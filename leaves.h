#ifndef _LEAVES_H_
#define _LEAVES_H_

/* Function templates for common tasks on linked/double-linked/tree structures */
/* Usage:
 *	struct my_obj { ...; my_obj *next; }			+
 *  LL_ADD_NEXT('test', my_obj, next);				=
 *	void test_my_obj_add_next(my_obj* node, my_obj* next) { }
 * Abbreviations:
 *  LL - linked list, DL - double linked list, LLT - linked list tree, 
 *  DLT - double linked list tree. "tree" means parent/child relations.
 */

#define EXT_LL_ADD_NEXT(SHORT, TYPE, NEXT) \
	extern void SHORT ## _add_next(TYPE *node, TYPE *next)
#define LL_ADD_NEXT(SHORT, TYPE, NEXT) \
	void SHORT ## _add_next(TYPE *node, TYPE *next) { \
		TYPE *last = node; \
		while (last-> NEXT) last = last-> NEXT ; \
		last-> NEXT = next; \
	}

#define EXT_LL_REMOVE(SHORT, TYPE, NEXT) \
	extern void SHORT ## _remove(TYPE *node, TYPE *remove)
#define LL_REMOVE(SHORT, TYPE, NEXT) \
	void SHORT ## _remove(TYPE *node, TYPE *remove) { \
		TYPE *prev = node; \
		TYPE *last = node-> NEXT; \
		while (last) { \
			if (last == remove) { \
				prev-> NEXT = remove-> NEXT ; \
				remove-> NEXT = NULL ; \
				break; \
			} \
			prev = last; \
			last = last-> NEXT ; \
		} \
	}

#define EXT_LL_FREE(SHORT, TYPE) \
	extern void SHORT ## _free(TYPE *node)
#define LL_FREE(SHORT, TYPE, NEXT, CODE) \
	void SHORT ## _free(TYPE *node) { \
		TYPE *next; \
		while (node) { \
			next = node-> NEXT ; \
			CODE ; \
			free(node); \
			node = next; \
		} \
	}

#define EXT_LL_PACKAGE(SHORT, TYPE, NEXT) \
	EXT_LL_ADD_NEXT(SHORT, TYPE, NEXT); \
	EXT_LL_REMOVE(SHORT, TYPE, NEXT); \
	EXT_LL_FREE(SHORT, TYPE)

#define LL_PACKAGE(SHORT, TYPE, NEXT, ON_FREE) \
	LL_ADD_NEXT(SHORT, TYPE, NEXT) \
	LL_REMOVE(SHORT, TYPE, NEXT) \
	LL_FREE(SHORT, TYPE, NEXT, ON_FREE)

#define EXT_LLT_ADD_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT) \
	extern void SHORT ## _add_child(TYPE *root, TYPE *child)
#define LLT_ADD_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT) \
	void SHORT ## _add_child(TYPE *root, TYPE *child) { \
		if (root-> CHILD == NULL) { \
			root-> CHILD = child; \
		} else { \
			TYPE *last = root-> CHILD ; \
			while (last-> NEXT) last = last-> NEXT ; \
			last-> NEXT = child; \
		} \
		child-> PARENT = root; \
	}

#define EXT_LLT_NUM_CHILDREN(SHORT, TYPE, CHILD, NEXT) \
	extern int SHORT ## _num_children(TYPE *root)
#define LLT_NUM_CHILDREN(SHORT, TYPE, CHILD, NEXT) \
	int SHORT ## _num_children(TYPE *root) { \
		int num = 0; \
		if (root-> CHILD != NULL) { \
			TYPE *last = root-> CHILD; \
			while (last) { num++; last = last-> NEXT ; } \
		} \
		return num; \
	}

#define EXT_LLT_COUNT(SHORT, TYPE, CHILD, NEXT) \
	extern int SHORT ## _count(TYPE *root)
#define LLT_COUNT(SHORT, TYPE, CHILD, NEXT) \
	int SHORT ## _count(TYPE *root) { \
		int num = 1; \
		if (root-> CHILD) num += SHORT ## _count(root-> CHILD); \
		if (root-> NEXT)  num += SHORT ## _count(root-> NEXT); \
		return num; \
	}

#define EXT_LLT_GET_CHILD(SHORT, TYPE, CHILD, NEXT) \
	extern TYPE * SHORT ## _get_child(TYPE *root, int id)
#define LLT_GET_CHILD(SHORT, TYPE, CHILD, NEXT) \
	TYPE * SHORT ## _get_child(TYPE *root, int id) { \
		int i = 0; \
		TYPE *last = root-> CHILD; \
		while (last != NULL) { \
			if (i++ == id) return last; \
			last = last-> NEXT ; \
		} \
		return NULL; \
	}

#define EXT_LLT_REMOVE_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT) \
	extern void SHORT ## _remove_child(TYPE *root, TYPE *child) 
#define LLT_REMOVE_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT) \
	void SHORT ## _remove_child(TYPE *root, TYPE *child) { \
		if (root-> CHILD == NULL) { \
			return;	\
		} else if (root-> CHILD == child) { \
			root-> CHILD = child-> NEXT; \
		} else { \
			TYPE *last = root-> CHILD; \
			while (last-> NEXT) { \
				if (last-> NEXT == child) { \
					last-> NEXT = child-> NEXT; \
					break; \
				} \
				last = last-> NEXT ; \
			} \
		} \
		child-> NEXT = NULL; \
		child-> PARENT = NULL; \
	}

#define EXT_LLT_PACKAGE(SHORT, TYPE, CHILD, NEXT, PARENT) \
	EXT_LLT_ADD_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT); \
	EXT_LLT_REMOVE_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT); \
	EXT_LLT_NUM_CHILDREN(SHORT, TYPE, CHILD, NEXT); \
	EXT_LLT_GET_CHILD(SHORT, TYPE, CHILD, NEXT)

#define LLT_PACKAGE(SHORT, TYPE, CHILD, NEXT, PARENT) \
	LLT_ADD_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT) \
	LLT_REMOVE_CHILD(SHORT, TYPE, CHILD, NEXT, PARENT) \
	LLT_NUM_CHILDREN(SHORT, TYPE, CHILD, NEXT) \
	LLT_GET_CHILD(SHORT, TYPE, CHILD, NEXT) \
	LLT_COUNT(SHORT, TYPE, CHILD, NEXT)

#define EXT_DLLT_ADD_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	extern void SHORT ## _add_child(TYPE *root, TYPE *child)
#define DLLT_ADD_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	void SHORT ## _add_child(TYPE *root, TYPE *child) { \
		if (root-> CHILD == NULL) { \
			root-> CHILD = child; \
		} else { \
			TYPE *last = root-> CHILD ; \
			while (last-> NEXT) last = last-> NEXT ; \
			last-> NEXT = child; \
			child-> PREV = last; \
		} \
		child-> PARENT = root; \
	}

#define EXT_DLLT_NUM_CHILDREN(SHORT, TYPE, CHILD, PREV, NEXT) \
	extern int SHORT ## _num_children(TYPE *root)
#define DLLT_NUM_CHILDREN(SHORT, TYPE, CHILD, PREV, NEXT) \
	int SHORT ## _num_children(TYPE *root) { \
		int num = 0; \
		if (root-> CHILD != NULL) { \
			TYPE *last = root-> CHILD; \
			while (last) { num++; last = last-> NEXT ; } \
		} \
		return num; \
	}

#define EXT_DLLT_COUNT(SHORT, TYPE, CHILD, PREV, NEXT) \
	extern int SHORT ## _count(TYPE *root)
#define DLLT_COUNT(SHORT, TYPE, CHILD, PREV, NEXT) \
	int SHORT ## _count(TYPE *root) { \
		int num = 1; \
		if (root-> CHILD) num += SHORT ## _count(root-> CHILD); \
		if (root-> NEXT)  num += SHORT ## _count(root-> NEXT); \
		return num; \
	}

#define EXT_DLLT_GET_CHILD(SHORT, TYPE, CHILD, PREV, NEXT) \
	extern TYPE * SHORT ## _get_child(TYPE *root, int id)
#define DLLT_GET_CHILD(SHORT, TYPE, CHILD, PREV, NEXT) \
	TYPE * SHORT ## _get_child(TYPE *root, int id) { \
		int i = 0; \
		TYPE *last = root-> CHILD; \
		while (last != NULL) { \
			if (i++ == id) return last; \
			last = last-> NEXT ; \
		} \
		return NULL; \
	}

#define EXT_DLLT_REMOVE_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	extern void SHORT ## _remove_child(TYPE *root, TYPE *child)
#define DLLT_REMOVE_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	void SHORT ## _remove_child(TYPE *root, TYPE *child) { \
		if (root-> CHILD == NULL) { \
			return;	\
		} else if (root-> CHILD == child) { \
			root-> CHILD = child-> NEXT; \
			child-> PREV = NULL; \
		} else { \
			TYPE *last = root-> CHILD; \
			while (last-> NEXT) { \
				if (last-> NEXT == child) { \
					last-> NEXT = child-> NEXT; \
					if (child-> NEXT) { \
						child-> NEXT -> PREV = last; \
					} \
					break; \
				} \
				last = last-> NEXT ; \
			} \
		} \
		child-> PREV = NULL; \
		child-> NEXT = NULL; \
		child-> PARENT = NULL; \
	}

#define EXT_DLLT_PACKAGE(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	EXT_DLLT_ADD_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT); \
	EXT_DLLT_REMOVE_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT); \
	EXT_DLLT_NUM_CHILDREN(SHORT, TYPE, CHILD, PREV, NEXT); \
	EXT_DLLT_GET_CHILD(SHORT, TYPE, CHILD, PREV, NEXT)

#define DLLT_PACKAGE(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	DLLT_ADD_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	DLLT_REMOVE_CHILD(SHORT, TYPE, CHILD, PREV, NEXT, PARENT) \
	DLLT_NUM_CHILDREN(SHORT, TYPE, CHILD, PREV, NEXT) \
	DLLT_GET_CHILD(SHORT, TYPE, CHILD, PREV, NEXT) \
	DLLT_COUNT(SHORT, TYPE, CHILD, PREV, NEXT)

#endif
