/*
* Author: Yanbing Wang <yawang@microsoft.com>

* Author: Bryan Berns <berns@uwalumni.com>
*   Updates to account for sidhistory checking
*
* Support file permission check on Win32 based operating systems.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// ReSharper disable CppClangTidyClangDiagnosticInvalidUtf8
#include <Windows.h>
#include <Sddl.h>
#include <Aclapi.h>
#include <errno.h>
#include <lm.h>
#include <stdio.h>

#include "inc\pwd.h"
#include "sshfileperm.h"
#include "debug.h"
#include "misc_internal.h"
#include "config.h"

#include <stdbool.h>

bool b_user_is_warned = false;

void show_no_chk_perm_warning(void)
{
  if(!b_user_is_warned)
  {
    printf("\n***************WARNING***************");
    printf("\nSpecial version of OpenSSH");
    printf("\nwhich does not check ");
    printf("\n    PRIVATE KEY FILE PERMISSIONS!");
    printf("\n***************WARNING***************");

    b_user_is_warned = true;
  }
}

/*
* The function is to check if current user is secure to access to the file.
* Check the owner of the file is one of these types: Local Administrators groups, system account, current user account
* Check the users have access permission to the file don't voilate the following rules:
  1. no user other than local administrators group, system account, and pwd user have write permission on the file
* Returns 0 on success and -1 on failure

Dino Capiaghi: 28.08.2028
=========================
Sorry but those rules are complete nonsense. Consequently, administrators and users are forced to do far more bad things to make key-files available
in most users' work environment than adding a second group for example!

But eve this was not enough! ...., as a final severe hit to every expert's common sense;
if not an crime against the ideal of the thinking human being at all:
       This behavior is not configurable by any option!

So, to prevent the worst from happening (file on USB stick, on local drive and so on)
I have no other choice as to disable this function in source until we have a
more relaxed a usefully version on hand to replace it.
*/
int
check_secure_file_permission(const char *input_path, struct passwd * pw, int read_ok)
{
  show_no_chk_perm_warning();
  return 0;
}

/*
* The function is similar to check_secure_file_permission.
* Check the owner of the file is one of these types: Local Administrators groups or system account
* Check the users have access permission to the file don't violate the following rules:
  1. no user other than local administrators group and system account have write permission on the folder
* Returns 0 on success and -1 on failure
*/
int
check_secure_folder_permission(const wchar_t* path_utf16, int read_ok)
{
  show_no_chk_perm_warning();
  return 0;
}
