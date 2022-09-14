/* $NetBSD: svc_auth.h,v 1.8 2000/06/02 22:57:57 fvdl Exp $ */

/*
 * Copyright (c) 2009, Sun Microsystems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of Sun Microsystems, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * from: @(#)svc_auth.h 1.6 86/07/16 SMI
 * @(#)svc_auth.h 2.1 88/07/29 4.0 RPCSRC
 * $FreeBSD: src/include/rpc/svc_auth.h,v 1.14 2002/03/23 17:24:55 imp Exp $
 */

/*
 * svc_auth.h, Service side of rpc authentication.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#ifndef _RPC_SVC_AUTH_H
#define _RPC_SVC_AUTH_H

#include <rpc/svc.h>

/*
 * Interface to server-side authentication flavors.
 */
typedef struct SVCAUTH {
	struct svc_auth_ops {
		bool(*svc_ah_wrap) (struct svc_req *, XDR *);
		bool(*svc_ah_unwrap) (struct svc_req *);
		bool(*svc_ah_checksum) (struct svc_req *);
		bool(*svc_ah_release) (struct svc_req *);
		bool(*svc_ah_destroy) (struct SVCAUTH *);
	} *svc_ah_ops;
	void *svc_ah_private;
} SVCAUTH;

#define SVCAUTH_WRAP(req, xdrs) \
	((*(((req)->rq_auth)->svc_ah_ops->svc_ah_wrap))(req, xdrs))

#define SVCAUTH_UNWRAP(req) \
	((*(((req)->rq_auth)->svc_ah_ops->svc_ah_unwrap))(req))

#define SVCAUTH_CHECKSUM(req) \
	((*(((req)->rq_auth)->svc_ah_ops->svc_ah_checksum))(req))

#define SVCAUTH_RELEASE(req) \
	((*(((req)->rq_auth)->svc_ah_ops->svc_ah_release))(req))

#define SVCAUTH_DESTROY(auth) \
	((*((auth)->svc_ah_ops->svc_ah_destroy))(auth))

/*
 * Server side authenticator
 */
#ifdef __cplusplus
extern "C" {
#endif
extern enum auth_stat svc_auth_authenticate(struct svc_req *, bool *);
extern int svc_auth_reg(int, enum auth_stat (*)(struct svc_req *));
#ifdef __cplusplus
}
#endif
#endif				/* !_RPC_SVC_AUTH_H */
