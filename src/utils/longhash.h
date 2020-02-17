#ifndef LONGHASH_H_INCLUDED
#define LONGHASH_H_INCLUDED
  
#ifdef __cplusplus
extern "C" {
#endif
  
typedef void (*longhash_void_free_fn)(void*);
  
struct _longhash;
typedef struct _longhash    longhash_t;
typedef struct _longhash *  longhash_pt;
  
longhash_pt
longhash_ctor(long in_num_bins,
        longhash_void_free_fn in_free_fn);
  
static inline longhash_pt
longhash_new(void) {
	return longhash_ctor(32, NULL);
}

static inline longhash_pt
longhash_new_dtor(longhash_void_free_fn in_free_fn) {
	return longhash_ctor(32, in_free_fn);
}

size_t
longhash_count(longhash_pt inp_self);

void
longhash_decref(longhash_pt inp_self);
  
void
longhash_dtor(longhash_pt *inpp);
  
void*
longhash_find(longhash_pt inp_self, long in_index);

long
longhash_insert(longhash_pt inp_self, long in_index, void *inp_val);
  
void*
longhash_remove(longhash_pt inp_self, long in_index);
  
long
longhash_delete(longhash_pt inp_self, long in_index);

#ifdef __cplusplus
}
#endif

#endif /* LONGHASH_H_INCLUDED */

