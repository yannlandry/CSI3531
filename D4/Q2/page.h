#ifndef PAGE_H
#define PAGE_H

struct page {
	int id;
	int present;
	int entered;
	int used;
};

struct page new_page();

#endif
