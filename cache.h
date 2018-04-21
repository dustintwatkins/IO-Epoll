#ifndef MARJ_CACHE_H
#define MARJ_CACHE_H

#include <stdlib.h>
#include "csapp.h"

typedef struct CachedItem CachedItem;

struct CachedItem {
  char url[MAXLINE];
  void *item_p;
  size_t size;
  CachedItem *prev;
  CachedItem *next;
};

typedef struct {
  size_t size;
  CachedItem* first;
  CachedItem* last;
} CacheList;

extern void cache_init(CacheList *list);
//size = 0
//first = NULL
//last = NULL
extern void cache_URL(char *URL, void *item, size_t size, CacheList *list);
//Check size, see if it fits in parameters 1mib
//Check space of linked list, evict if necessary(while needed)
//malloc cached item (sizeof(CachedItem))
//Connect to front of the list append_to_front()

extern void evict(CacheList *list);
//go to *last
//last_size = sizeof(*last)
//then go to prev
//free(last) then set prev->NULL
//assign *last to *prev
//update list size -= last_size

extern CachedItem *find(char *URL, CacheList *list);
//iterate through *list
//if url == list.url
//  return CachedItem
//return NULL if no URL is in the list

//extern CachedItem get_cache(char *URL, CacheList *list);

extern void move_to_front(char *URL, CacheList *list);
//go to item and check if its there, if not rerturn
//if url == *first->url
//  return
//if *first == *last
//if *last.url == url
//  update list->last = item->prev
//  list->first->prev = item
//  item->next = first
//  item->prev = NULL
//  last->next = NULL
//  first = item
//  return
//Now we check if it is in the middle instead
//  item->prev->next = item->next
//  item->next->prev = item->prev
//  item->prev = NULL
//  item->next = list->first
//  list->first->prev = item
//  list->first = item

extern void print_URLs(CacheList *list);

extern void cache_destruct(CacheList *list);
//Free the cache, start at end then go prev and free as you go
#endif
