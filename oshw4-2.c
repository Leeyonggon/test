#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<fcntl.h>
#include	<sys/shm.h>
#include	<sys/stat.h>
#include	<sys/mman.h>
#include	<sys/types.h>
int	main()
{
	const	char	*name	=	"OS";			/*	name	of	shared	memory	object	*/
	const	int	SIZE	=	4096;					/*	size	of	shared	memory	object	*/
	int	shm_fd;													/*	file	descriptor	of	shared	memory	*/
	void	*ptr;														/*	pointer	to	shared	memory	object	*/
	const	char	*message0=	"Studying	";
	const	char	*message1=	"Operating	Systems	";
	const	char	*message2=	"Is	Fun!";
	/*	create	the	shared	memory	segment	*/
	shm_fd	=	shm_open(name,	O_CREAT	|	O_RDWR,	0666);
	if	(shm_fd	==	-1)	{
		printf("shared	memory	failed\n");
		exit(-1);
	}
	/*	configure	the	size	of	the	shared	memory	segment	*/
	ftruncate(shm_fd,	SIZE);
	/*	map	the	shared	memory	segment	in	the	address	space	of	the	process	*/
	ptr	=	mmap(0,SIZE,	PROT_READ	|	PROT_WRITE,	MAP_SHARED,	shm_fd,	0);
	if	(ptr	==	MAP_FAILED)	{
		printf("Map	failed\n");
		exit(-1);
	}
	/*	write	to	the	shared	memory	region	*/
	sprintf(ptr,	"%s",	message0);
	ptr	+=	strlen(message0);								/*	increment	ptr	*/
	sprintf(ptr,	"%s",	message1);
	ptr	+=	strlen(message1);								/*	increment	ptr	*/
	sprintf(ptr,	"%s",	message2);
	ptr	+=	strlen(message2);								/*	increment	ptr	*/
	return	0;
}