#ifndef __DEBUG_H__
#define __DEBUG_H__

//TODO implement this with vargs

/*
 * Basic DEBUG-level printing.
 * NOTE, here we only provide a printing of a simple string
 */
//void debug(char* s);
 #define debug printf

/*
 * INFO-level printings.
 */
//void info(const char* s);
#define info printf

/*
 * ERROR-level printing.
 */
//void error(const char* s);
#define error printf

#endif