What is this repo?
==================

This repo, 'clarity20/bash', is a fork of bash-5.2 that shows how to develop and build a 
"bash function library" as a shared object for use with `clarity20/bash2py`. You should be able to 
build the shared object `libbash.so` by following the steps in the (modified) document `INSTALL` 
included in this package. If you are working with another version of bash we invite you to download
its source from `bminor/bash`, apply the changes seen here, and build the `*.so` you need. 

Our goal is to cleanly separate `bash` from `bash2py` starting with `bash2py-4.0` so the latter 
can be bash-version-agnostic. This will make `bash2py` more versatile while enabling us to 
clean up the project space for future work. 

Technical details
=================

We need to remove bash's function main() from `libbash.so` to avoid a name clash with the 
main() function of `bash2py`. One way is to rename main() in the `bash` source code, as in 
the branch `renamed_main`. Another way is to separate it into another module as in the branch 
`with_separate_main`. The former is an easier and cleaner fix, but the latter offers an easy
sanity check by building `bash[.exe]` from `libbash.so`.

As for `bash2py`'s many deltas from `bash`, we have to selectively override `libbash.so`'s behavior 
from the outside. Fortunately the GNU C compiler provides a NON-STANDARD mechanism for this in
the `--wrap` compiler flag. See, for instance, question 46444052 on Stack Overflow, "How to wrap 
functions with the `--wrap` option correctly?" But (adroit) usage of the `--wrap` option 
concerns the `bash2py` project only. We will not discuss it here.

The standard `bash` README follows.

Introduction
============

This is GNU Bash, version 5.2. Bash is the GNU Project's Bourne
Again SHell, a complete implementation of the POSIX shell spec,
but also with interactive command line editing, job control on
architectures that support it, csh-like features such as history
substitution and brace expansion, and a slew of other features. 
For more information on the features of Bash that are new to this
type of shell, see the file `doc/bashref.texi'.  There is also a
large Unix-style man page.  The man page is the definitive description
of the shell's features. 

See the file POSIX for a discussion of how the Bash defaults differ
from the POSIX spec and a description of the Bash `posix mode'.

There are some user-visible incompatibilities between this version
of Bash and previous widely-distributed versions, bash-4.4, bash-5.0,
and bash-5.1. For details, see the file COMPAT.  The NEWS file tersely
lists features that are new in this release. 

Bash is free software, distributed under the terms of the [GNU] General
Public License as published by the Free Software Foundation,
version 3 of the License (or any later version).  For more information,
see the file COPYING. 

A number of frequently-asked questions are answered in the file
`doc/FAQ'. (That file is no longer updated.)

To compile Bash, type `./configure', then `make'.  Bash auto-configures
the build process, so no further intervention should be necessary.  Bash
builds with `gcc' by default if it is available.  If you want to use `cc'
instead, type

	CC=cc ./configure

if you are using a Bourne-style shell.  If you are not, the following
may work:

	env CC=cc ./configure

Read the file INSTALL in this directory for more information about how
to customize and control the build process.  The file NOTES contains
platform-specific installation and configuration information.

If you are a csh user and wish to convert your csh aliases to Bash
aliases, you may wish to use the script `examples/misc/alias-conv.sh'
as a starting point.  The script `examples/misc/cshtobash' is a
more ambitious script that attempts to do a more complete job.

Reporting Bugs
==============

Bug reports for bash should be sent to:

	bug-bash@gnu.org

using the `bashbug' program that is built and installed at the same
time as bash.

The discussion list `bug-bash@gnu.org' often contains information
about new ports of Bash, or discussions of new features or behavior
changes that people would like.  This mailing list is also available
as a usenet newsgroup: gnu.bash.bug. 

When you send a bug report, please use the `bashbug' program that is
built at the same time as bash.  If bash fails to build, try building
bashbug directly with `make bashbug'.  If you cannot build `bashbug',
please send mail to bug-bash@gnu.org with the following information:

	* the version number and release status of Bash (e.g., 2.05a-release)
	* the machine and OS that it is running on (you may run
	  `bashversion -l' from the bash build directory for this information)
	* a list of the compilation flags or the contents of `config.h', if
	  appropriate
	* a description of the bug
	* a recipe for recreating the bug reliably
	* a fix for the bug if you have one!

The `bashbug' program includes much of this automatically.

Questions and requests for help with bash and bash programming may be
sent to the help-bash@gnu.org mailing list.

If you would like to contact the Bash maintainers directly, send mail
to bash-maintainers@gnu.org.

While the Bash maintainers do not promise to fix all bugs, we would
like this shell to be the best that we can make it.

Other Packages
==============

This distribution includes, in examples/bash-completion, a recent version
of the `bash-completion' package, which provides programmable completions
for a number of commands. It's available as a package in many distributions,
and that is the first place from which to obtain it.

The latest version of bash-completion is always available from
https://github.com/scop/bash-completion.

If it's not a package from your vendor, you may install the included version.

Enjoy!

Chet Ramey
chet.ramey@case.edu

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.  This file is offered as-is,
without any warranty.
