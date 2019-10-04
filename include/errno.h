#ifndef __ERRNO_H__
#define __ERRNO_H__

char *error_map[] = {
	"EPERM\n",	/* Not super-user */
	"ENOENT\n",	/* No such file or directory */
	"ESRCH\n",	/* No such process */
	"EINTR\n",	/* Interrupted system call */
	"EIO\n",		/* I/O error */
	"ENXIO\n",	/* No such device or address */
	"E2BIG\n",	/* Arg list too long */
	"ENOEXEC\n",	/* Exec format error */
	"EBADF\n",	/* Bad file number */
	"ECHILD\n",	/* No children */
	"EAGAIN\n",	/* No more processes */
	"ENOMEM\n",	/* Not enough core */
	"EACCES\n",	/* Permission denied */
	"EFAULT\n",	/* Bad address */
	"ENOTBLK\n",	/* Block device required */
	"EBUSY\n",	/* Mount device busy */
	"EEXIST\n",	/* File exists */
	"EXDEV\n",	/* Cross-device link */
	"ENODEV\n",	/* No such device */
	"ENOTDIR\n",	/* Not a directory */
	"EISDIR\n",	/* Is a directory */
	"EINVAL\n",	/* Invalid argument */
	"ENFILE\n",	/* Too many open files in system */
	"EMFILE\n",	/* Too many open files */
	"ENOTTY\n",	/* Not a typewriter */
	"ETXTBSY\n",	/* Text file busy */
	"EFBIG\n",	/* File too large */
	"ENOSPC\n",	/* No space left on device */
	"ESPIPE\n",	/* Illegal seek */
	"EROFS\n",	/* Read only file system */
	"EMLINK\n",	/* Too many links */
	"EPIPE\n",	/* Broken pipe */
	"EDOM\n",		/* Math arg out of domain of func */
	"ERANGE\n",	/* Math result not representable */
	"ENOMSG\n",	/* No message of desired type */
	"EIDRM\n",	/* Identifier removed */
	"ECHRNG\n",	/* Channel number out of range */
	"EL2NSYNC\n",	/* Level 2 not synchronized */
	"EL3HLT\n",	/* Level 3 halted */
	"EL3RST\n",	/* Level 3 reset */
	"ELNRNG\n",	/* Link number out of range */
	"EUNATCH\n",	/* Protocol driver not attached */
	"ENOCSI\n",	/* No CSI structure available */
	"EL2HLT\n",	/* Level 2 halted */
	"EDEADLK\n",	/* Deadlock condition */
	"ENOLCK\n",	/* No record locks available */
	"EBADE\n",	/* Invalid exchange */
	"EBADR\n",	/* Invalid request descriptor */
	"EXFULL\n",	/* Exchange full */
	"ENOANO\n",	/* No anode */
	"EBADRQC\n",	/* Invalid request code */
	"EBADSLT\n",	/* Invalid slot */
	"EDEADLOCK\n",/* File locking deadlock error */
	"EBFONT\n",	/* Bad font file fmt */
	"ENOSTR\n",	/* Device not a stream */
	"ENODATA\n",	/* No data (for no delay io) */
	"ETIME\n",	/* Timer expired */
	"ENOSR\n",	/* Out of streams resources */
	"ENONET\n",	/* Machine is not on the network */
	"ENOPKG\n",	/* Package not installed */
	"EREMOTE\n",	/* The object is remote */
	"ENOLINK\n",	/* The link has been severed */
	"EADV\n",		/* Advertise error */
	"ESRMNT\n",	/* Srmount error */
	"ECOMM\n",	/* Communication error on send */
	"EPROTO\n",	/* Protocol error */
	"EMULTIHOP\n",/* Multihop attempted */
	"ELBIN\n",	/* Inode is remote (not really error) */
	"EDOTDOT\n",	/* Cross mount point (not really error) */
	"EBADMSG\n",	/* Trying to read unreadable message */
	"EFTYPE\n",	/* Inappropriate file type or format */
	"ENOTUNIQ\n",	/* Given log. name not unique */
	"EBADFD\n",	/* f.d. invalid for this operation */
	"EREMCHG\n",	/* Remote address changed */
	"ELIBACC\n",	/* Can't access a needed shared lib */
	"ELIBBAD\n",	/* Accessing a corrupted shared lib */
	"ELIBSCN\n",	/* .lib section in a.out corrupted */
	"ELIBMAX\n",	/* Attempting to link in too many libs */
	"ELIBEXEC\n",	/* Attempting to exec a shared library */
	"ENOSYS\n",	/* Function not implemented */
	"ENMFILE\n",	/* No more files */
	"ENOTEMPTY\n",	/* Directory not empty */
	"ENAMETOOLONG\n",	/* File or path name too long */
	"ELOOP\n",	/* Too many symbolic links */
	"EOPNOTSUPP\n",	/* Operation not supported on transport endpoint */
	"EPFNOSUPPORT\n",	/* Protocol family not supported */
	"ECONNRESET\n",	/* Connection reset by peer */
	"ENOBUFS\n",	/* No buffer space available */
	"EAFNOSUPPORT\n",	/* Address family not supported by protocol family */
	"EPROTOTYPE\n",	/* Protocol wrong type for socket */
	"ENOTSOCK\n",	/* Socket operation on non-socket */
	"ENOPROTOOPT\n",	/* Protocol not available */
	"ESHUTDOWN\n",	/* Can't send after socket shutdown */
	"ECONNREFUSED\n",	/* Connection refused */
	"EADDRINUSE\n",	/* Address already in use */
	"ECONNABORTED\n",	/* Connection aborted */
	"ENETUNREACH\n",	/* Network is unreachable */
	"ENETDOWN\n",	/* Network interface is not configured */
	"ETIMEDOUT\n",	/* Connection timed out */
	"EHOSTDOWN\n",	/* Host is down */
	"EHOSTUNREACH\n",	/* Host is unreachable */
	"EINPROGRESS\n",	/* Connection already in progress */
	"EALREADY\n",	/* Socket already connected */
	"EDESTADDRREQ\n",	/* Destination address required */
	"EMSGSIZE\n",	/* Message too long */
	"EPROTONOSUPPORT\n",	/* Unknown protocol */
	"ESOCKTNOSUPPORT\n",	/* Socket type not supported */
	"EADDRNOTAVAIL\n",	/* Address not available */
	"ENETRESET\n",
	"EISCONN\n",	/* Socket is already connected */
	"ENOTCONN\n",	/* Socket is not connected */
	"ETOOMANYREFS\n",
	"EPROCLIM\n",
	"EUSERS\n",
	"EDQUOT\n",
	"ESTALE\n",
	"ENOTSUP\n",	/* Not supported */
	"ENOMEDIUM\n",	/* No medium (in tape drive) */
	"ENOSHARE\n",	/* No such host or network path */
	"ECASECLASH\n",	/* Filename exists with different case */
	"EILSEQ\n",
	"EOVERFLOW\n",	/* Value too large for defined data type */
	"EWOULDBLOCK EAGAIN\n",	/* Operation would block */
	"__ELASTERROR"	/* Users can add values starting here */
};

#endif