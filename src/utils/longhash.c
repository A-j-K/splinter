#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
  
#include "longhash.h"
  
#ifdef __cplusplus
extern "C" {
#endif
  
struct _longhash_bin;
typedef struct _longhash_bin    longhash_bin_t;
typedef struct _longhash_bin *  longhash_bin_pt;
typedef struct _longhash_bin ** longhash_bin_ppt;
  
struct _longhash_bin
{
	int		n_index;
	void*           p_value;
	longhash_bin_pt  p_next;
};
  
struct _longhash
{
	size_t                num_of_entries;
	int                   num_of_bins;
	int                   bin_mask;
	longhash_void_free_fn  p_bin_void_free_fn;
	longhash_bin_ppt       p_bins;
	pthread_mutex_t       lock;
};
  
longhash_pt
longhash_ctor(long in_num_bins, longhash_void_free_fn in_free_fn)
{
	longhash_pt p_self = (longhash_pt)calloc(1, sizeof(longhash_t));
	if(p_self) {
		long i = 3;
		p_self->num_of_bins = in_num_bins;
		if(in_num_bins >= 0x80000000) {
			p_self->num_of_bins = 0x80000000;
		}
		else {
			while((1U << i) < in_num_bins) {
				++i;
			}
			p_self->num_of_bins = 1 << i;
		}
		p_self->bin_mask = p_self->num_of_bins - 1;
		p_self->p_bin_void_free_fn = in_free_fn;
		p_self->p_bins = (longhash_bin_ppt)calloc(p_self->num_of_bins,
			sizeof(longhash_bin_ppt));
		if(!p_self->p_bins) {
			goto longhash_ctor_fail;
		}
		if(pthread_mutex_init(&p_self->lock, NULL) != 0) {
			goto longhash_ctor_fail;
		}
	}
	return p_self;

longhash_ctor_fail:
	if(p_self) {
		longhash_dtor(&p_self);
	}
	return NULL;
}
  
static longhash_bin_pt
longhash_bin_free(longhash_bin_pt inp_self, longhash_void_free_fn in_fnf)
{
	longhash_bin_pt p_next = NULL;
	if(inp_self) {
		p_next = inp_self->p_next;
		if(in_fnf && inp_self->p_value) {
			(in_fnf)(inp_self->p_value);
		}
		free(inp_self);
	}
	return p_next;
}
  
void
longhash_decref(longhash_pt inp_self)
{
	if(inp_self) {
		pthread_mutex_lock(&inp_self->lock);	
		for(long i = 0; i < inp_self->num_of_bins; i++) {
			longhash_bin_pt p_next = longhash_bin_free(inp_self->p_bins[i],
			   inp_self->p_bin_void_free_fn);
			inp_self->p_bins[i] = 0;
			while(p_next != NULL) {
				p_next = longhash_bin_free(p_next,
				   inp_self->p_bin_void_free_fn);
			}
		}
		pthread_mutex_unlock(&inp_self->lock);
		pthread_mutex_destroy(&inp_self->lock);
		free(inp_self->p_bins);
		free(inp_self);
	}
}
  
void
longhash_dtor(longhash_pt *inpp)
{
	if(inpp) {
		longhash_pt p_self = *inpp;
		if(p_self) longhash_decref(p_self);
		*inpp = NULL;
	}
}
  
void*
longhash_find(longhash_pt inp_self, long in_index) 
{
	long bin;
	void *p_rval = NULL;
	if(pthread_mutex_lock(&inp_self->lock) != 0) {
		return NULL;
	}
	bin = in_index & inp_self->bin_mask;
	longhash_bin_pt p_bin = (longhash_bin_pt)inp_self->p_bins[bin];
	while(p_bin) {
		if(in_index == p_bin->n_index) {
			p_rval = p_bin->p_value;
			pthread_mutex_unlock(&inp_self->lock);
			return p_rval; 
		}
		p_bin = p_bin->p_next;
	}
	pthread_mutex_unlock(&inp_self->lock);
	return p_rval;
}
  
long
longhash_insert(longhash_pt inp_self, long in_index, void *inp_val)
{
	long bin;
	if(longhash_find(inp_self, in_index) != NULL) {
		longhash_delete(inp_self, in_index);
	}
	if(pthread_mutex_lock(&inp_self->lock) != 0) {
		return -1;
	}
	longhash_bin_pt p_bin = calloc(1, sizeof(longhash_bin_t));
	if(!p_bin) {
		pthread_mutex_unlock(&inp_self->lock);
		return -1;
	}
	p_bin->p_value = inp_val;
	p_bin->n_index = in_index;
	bin = in_index & inp_self->bin_mask;
	if(!inp_self->p_bins[bin]) {
		inp_self->p_bins[bin] = p_bin;
	}
	else {
		p_bin->p_next = inp_self->p_bins[bin];
		inp_self->p_bins[bin] = p_bin;
	}
	inp_self->num_of_entries++;
	pthread_mutex_unlock(&inp_self->lock);
	return 0;
}
  
void*
longhash_remove(longhash_pt inp_self, long in_index)
{
	long bin;
	void *p_rval = NULL;
	if(pthread_mutex_lock(&inp_self->lock) != 0) {
		return NULL;
	}
	p_rval = NULL;
	bin = in_index & inp_self->bin_mask;
	longhash_bin_pt p_prev = NULL, p_bin = inp_self->p_bins[bin];
	while(p_bin) {
		if(in_index == p_bin->n_index) { 
			if(p_prev) {
				p_prev->p_next = p_bin->p_next;
			}
			else {
				inp_self->p_bins[bin] = p_bin->p_next;
			}
			inp_self->num_of_entries--;
			p_rval = p_bin->p_value;
			longhash_bin_free(p_bin, NULL);
			pthread_mutex_unlock(&inp_self->lock);
			return p_rval;
		}
		p_prev = p_bin;
		p_bin = p_bin->p_next;
	}
	pthread_mutex_unlock(&inp_self->lock);
	return p_rval;
}
  
long
longhash_delete(longhash_pt inp_self, long in_index)
{
	long bin;
	if(pthread_mutex_lock(&inp_self->lock) != 0) {
		return -1;
	}
	bin = in_index & inp_self->bin_mask;
	longhash_bin_pt p_prev = NULL, p_bin = inp_self->p_bins[bin];
	while(p_bin) {
		if(in_index == p_bin->n_index) { 
			if(p_prev) {
				p_prev->p_next = p_bin->p_next;
			}
			else {
				inp_self->p_bins[bin] = p_bin->p_next;
			}
			longhash_bin_free(p_bin, inp_self->p_bin_void_free_fn);
			inp_self->num_of_entries--;
			pthread_mutex_unlock(&inp_self->lock);
			return 0;
		}
		p_prev = p_bin;
		p_bin = p_bin->p_next;
	}
	pthread_mutex_unlock(&inp_self->lock);
	return 1;
}

size_t
longhash_count(longhash_pt inp_self)
{
	size_t rval;
	if(pthread_mutex_lock(&inp_self->lock) != 0) {
		return -1;
	}
	rval = inp_self->num_of_entries;
	pthread_mutex_unlock(&inp_self->lock);
	return rval;
}
  

#ifdef __cplusplus
}
#endif

