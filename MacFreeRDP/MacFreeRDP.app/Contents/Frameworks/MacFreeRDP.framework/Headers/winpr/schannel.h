/**
 * WinPR: Windows Portable Runtime
 * Schannel Security Package
 *
 * Copyright 2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WINPR_SSPI_SCHANNEL_H
#define WINPR_SSPI_SCHANNEL_H

#include <winpr/sspi.h>
#include <winpr/crypto.h>

#if defined(_WIN32) && !defined(_UWP)

#include <schannel.h>

#else

#define SCHANNEL_NAME_A		"Schannel"
#define SCHANNEL_NAME_W		L"Schannel"

#ifdef _UNICODE
#define SCHANNEL_NAME	SCHANNEL_NAME_W
#else
#define SCHANNEL_NAME	SCHANNEL_NAME_A
#endif

#define SECPKG_ATTR_SUPPORTED_ALGS		86
#define SECPKG_ATTR_CIPHER_STRENGTHS		87
#define SECPKG_ATTR_SUPPORTED_PROTOCOLS		88

typedef struct _SecPkgCred_SupportedAlgs
{
	DWORD cSupportedAlgs;
	ALG_ID* palgSupportedAlgs;
} SecPkgCred_SupportedAlgs, *PSecPkgCred_SupportedAlgs;

typedef struct _SecPkgCred_CipherStrengths
{
	DWORD dwMinimumCipherStrength;
	DWORD dwMaximumCipherStrength;
} SecPkgCred_CipherStrengths, *PSecPkgCred_CipherStrengths;

typedef struct _SecPkgCred_SupportedProtocols
{
	DWORD grbitProtocol;
} SecPkgCred_SupportedProtocols, *PSecPkgCred_SupportedProtocols;

enum eTlsSignatureAlgorithm
{
	TlsSignatureAlgorithm_Anonymous = 0,
	TlsSignatureAlgorithm_Rsa = 1,
	TlsSignatureAlgorithm_Dsa = 2,
	TlsSignatureAlgorithm_Ecdsa = 3
};

enum eTlsHashAlgorithm
{
	TlsHashAlgorithm_None = 0,
	TlsHashAlgorithm_Md5 = 1,
	TlsHashAlgorithm_Sha1 = 2,
	TlsHashAlgorithm_Sha224 = 3,
	TlsHashAlgorithm_Sha256 = 4,
	TlsHashAlgorithm_Sha384 = 5,
	TlsHashAlgorithm_Sha512 = 6
};

#define SCH_CRED_V1			0x00000001
#define SCH_CRED_V2			0x00000002
#define SCH_CRED_VERSION		0x00000002
#define SCH_CRED_V3			0x00000003
#define SCHANNEL_CRED_VERSION		0x00000004

struct _HMAPPER;

typedef struct _SCHANNEL_CRED
{
	DWORD dwVersion;
	DWORD cCreds;
	PCCERT_CONTEXT* paCred;
	HCERTSTORE hRootStore;

	DWORD cMappers;
	struct _HMAPPER **aphMappers;

	DWORD cSupportedAlgs;
	ALG_ID* palgSupportedAlgs;

	DWORD grbitEnabledProtocols;
	DWORD dwMinimumCipherStrength;
	DWORD dwMaximumCipherStrength;
	DWORD dwSessionLifespan;
	DWORD dwFlags;
	DWORD dwCredFormat;
} SCHANNEL_CRED, *PSCHANNEL_CRED;

#define SCH_CRED_FORMAT_CERT_CONTEXT		0x00000000
#define SCH_CRED_FORMAT_CERT_HASH		0x00000001
#define SCH_CRED_FORMAT_CERT_HASH_STORE		0x00000002

#define SCH_CRED_MAX_STORE_NAME_SIZE		128
#define SCH_CRED_MAX_SUPPORTED_ALGS		256
#define SCH_CRED_MAX_SUPPORTED_CERTS		100

typedef struct _SCHANNEL_CERT_HASH
{
	DWORD dwLength;
	DWORD dwFlags;
	HCRYPTPROV hProv;
	BYTE ShaHash[20];
} SCHANNEL_CERT_HASH, *PSCHANNEL_CERT_HASH;

typedef struct _SCHANNEL_CERT_HASH_STORE
{
    DWORD dwLength;
    DWORD dwFlags;
    HCRYPTPROV hProv;
    BYTE ShaHash[20];
    WCHAR pwszStoreName[SCH_CRED_MAX_STORE_NAME_SIZE];
} SCHANNEL_CERT_HASH_STORE, *PSCHANNEL_CERT_HASH_STORE;

#define SCH_MACHINE_CERT_HASH				0x00000001

#define SCH_CRED_NO_SYSTEM_MAPPER			0x00000002
#define SCH_CRED_NO_SERVERNAME_CHECK			0x00000004
#define SCH_CRED_MANUAL_CRED_VALIDATION			0x00000008
#define SCH_CRED_NO_DEFAULT_CREDS			0x00000010
#define SCH_CRED_AUTO_CRED_VALIDATION			0x00000020
#define SCH_CRED_USE_DEFAULT_CREDS			0x00000040
#define SCH_CRED_DISABLE_RECONNECTS			0x00000080

#define SCH_CRED_REVOCATION_CHECK_END_CERT		0x00000100
#define SCH_CRED_REVOCATION_CHECK_CHAIN			0x00000200
#define SCH_CRED_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT	0x00000400
#define SCH_CRED_IGNORE_NO_REVOCATION_CHECK		0x00000800
#define SCH_CRED_IGNORE_REVOCATION_OFFLINE		0x00001000

#define SCH_CRED_RESTRICTED_ROOTS			0x00002000
#define SCH_CRED_REVOCATION_CHECK_CACHE_ONLY		0x00004000
#define SCH_CRED_CACHE_ONLY_URL_RETRIEVAL		0x00008000

#define SCH_CRED_MEMORY_STORE_CERT			0x00010000

#define SCH_CRED_CACHE_ONLY_URL_RETRIEVAL_ON_CREATE	0x00020000

#define SCH_SEND_ROOT_CERT				0x00040000
#define SCH_CRED_SNI_CREDENTIAL				0x00080000
#define SCH_CRED_SNI_ENABLE_OCSP			0x00100000
#define SCH_SEND_AUX_RECORD				0x00200000

#define SCHANNEL_RENEGOTIATE		0
#define SCHANNEL_SHUTDOWN		1
#define SCHANNEL_ALERT			2
#define SCHANNEL_SESSION		3

typedef struct _SCHANNEL_ALERT_TOKEN
{
	DWORD dwTokenType;
	DWORD dwAlertType;
	DWORD dwAlertNumber;
} SCHANNEL_ALERT_TOKEN;

#define TLS1_ALERT_WARNING			1
#define TLS1_ALERT_FATAL			2

#define TLS1_ALERT_CLOSE_NOTIFY			0
#define TLS1_ALERT_UNEXPECTED_MESSAGE		10
#define TLS1_ALERT_BAD_RECORD_MAC		20
#define TLS1_ALERT_DECRYPTION_FAILED		21
#define TLS1_ALERT_RECORD_OVERFLOW		22
#define TLS1_ALERT_DECOMPRESSION_FAIL		30
#define TLS1_ALERT_HANDSHAKE_FAILURE		40
#define TLS1_ALERT_BAD_CERTIFICATE		42
#define TLS1_ALERT_UNSUPPORTED_CERT		43
#define TLS1_ALERT_CERTIFICATE_REVOKED		44
#define TLS1_ALERT_CERTIFICATE_EXPIRED		45
#define TLS1_ALERT_CERTIFICATE_UNKNOWN		46
#define TLS1_ALERT_ILLEGAL_PARAMETER		47
#define TLS1_ALERT_UNKNOWN_CA			48
#define TLS1_ALERT_ACCESS_DENIED		49
#define TLS1_ALERT_DECODE_ERROR			50
#define TLS1_ALERT_DECRYPT_ERROR		51
#define TLS1_ALERT_EXPORT_RESTRICTION		60
#define TLS1_ALERT_PROTOCOL_VERSION		70
#define TLS1_ALERT_INSUFFIENT_SECURITY		71
#define TLS1_ALERT_INTERNAL_ERROR		80
#define TLS1_ALERT_USER_CANCELED		90
#define TLS1_ALERT_NO_RENEGOTIATION		100
#define TLS1_ALERT_UNSUPPORTED_EXT		110

#define SSL_SESSION_ENABLE_RECONNECTS		1
#define SSL_SESSION_DISABLE_RECONNECTS		2

typedef struct _SCHANNEL_SESSION_TOKEN
{
	DWORD dwTokenType;
	DWORD dwFlags;
} SCHANNEL_SESSION_TOKEN;

typedef struct _SCHANNEL_CLIENT_SIGNATURE
{
	DWORD cbLength;
	ALG_ID aiHash;
	DWORD cbHash;
	BYTE HashValue[36];
	BYTE CertThumbprint[20];
} SCHANNEL_CLIENT_SIGNATURE, *PSCHANNEL_CLIENT_SIGNATURE;

#define SP_PROT_SSL3_SERVER		0x00000010
#define SP_PROT_SSL3_CLIENT		0x00000020
#define SP_PROT_SSL3			(SP_PROT_SSL3_SERVER | SP_PROT_SSL3_CLIENT)

#define SP_PROT_TLS1_SERVER		0x00000040
#define SP_PROT_TLS1_CLIENT		0x00000080
#define SP_PROT_TLS1			(SP_PROT_TLS1_SERVER | SP_PROT_TLS1_CLIENT)

#define SP_PROT_SSL3TLS1_CLIENTS	(SP_PROT_TLS1_CLIENT | SP_PROT_SSL3_CLIENT)
#define SP_PROT_SSL3TLS1_SERVERS	(SP_PROT_TLS1_SERVER | SP_PROT_SSL3_SERVER)
#define SP_PROT_SSL3TLS1		(SP_PROT_SSL3 | SP_PROT_TLS1)

#define SP_PROT_UNI_SERVER		0x40000000
#define SP_PROT_UNI_CLIENT		0x80000000
#define SP_PROT_UNI			(SP_PROT_UNI_SERVER | SP_PROT_UNI_CLIENT)

#define SP_PROT_ALL			0xFFFFFFFF
#define SP_PROT_NONE			0
#define SP_PROT_CLIENTS			(SP_PROT_SSL3_CLIENT | SP_PROT_UNI_CLIENT | SP_PROT_TLS1_CLIENT)
#define SP_PROT_SERVERS			(SP_PROT_SSL3_SERVER | SP_PROT_UNI_SERVER | SP_PROT_TLS1_SERVER)

#define SP_PROT_TLS1_0_SERVER		SP_PROT_TLS1_SERVER
#define SP_PROT_TLS1_0_CLIENT		SP_PROT_TLS1_CLIENT
#define SP_PROT_TLS1_0			(SP_PROT_TLS1_0_SERVER | SP_PROT_TLS1_0_CLIENT)

#define SP_PROT_TLS1_1_SERVER		0x00000100
#define SP_PROT_TLS1_1_CLIENT		0x00000200
#define SP_PROT_TLS1_1			(SP_PROT_TLS1_1_SERVER | SP_PROT_TLS1_1_CLIENT)

#define SP_PROT_TLS1_2_SERVER		0x00000400
#define SP_PROT_TLS1_2_CLIENT		0x00000800
#define SP_PROT_TLS1_2			(SP_PROT_TLS1_2_SERVER | SP_PROT_TLS1_2_CLIENT)

#define SP_PROT_DTLS_SERVER		0x00010000
#define SP_PROT_DTLS_CLIENT		0x00020000
#define SP_PROT_DTLS			(SP_PROT_DTLS_SERVER | SP_PROT_DTLS_CLIENT)

#define SP_PROT_DTLS1_0_SERVER		SP_PROT_DTLS_SERVER
#define SP_PROT_DTLS1_0_CLIENT		SP_PROT_DTLS_CLIENT
#define SP_PROT_DTLS1_0			(SP_PROT_DTLS1_0_SERVER | SP_PROT_DTLS1_0_CLIENT)

#define SP_PROT_DTLS1_X_SERVER		SP_PROT_DTLS1_0_SERVER

#define SP_PROT_DTLS1_X_CLIENT		SP_PROT_DTLS1_0_CLIENT

#define SP_PROT_DTLS1_X			(SP_PROT_DTLS1_X_SERVER | SP_PROT_DTLS1_X_CLIENT)

#define SP_PROT_TLS1_1PLUS_SERVER	(SP_PROT_TLS1_1_SERVER | SP_PROT_TLS1_2_SERVER)
#define SP_PROT_TLS1_1PLUS_CLIENT	(SP_PROT_TLS1_1_CLIENT | SP_PROT_TLS1_2_CLIENT)

#define SP_PROT_TLS1_1PLUS		(SP_PROT_TLS1_1PLUS_SERVER | SP_PROT_TLS1_1PLUS_CLIENT)

#define SP_PROT_TLS1_X_SERVER		(SP_PROT_TLS1_0_SERVER | SP_PROT_TLS1_1_SERVER | SP_PROT_TLS1_2_SERVER)
#define SP_PROT_TLS1_X_CLIENT		(SP_PROT_TLS1_0_CLIENT | SP_PROT_TLS1_1_CLIENT | SP_PROT_TLS1_2_CLIENT)
#define SP_PROT_TLS1_X			(SP_PROT_TLS1_X_SERVER | SP_PROT_TLS1_X_CLIENT)

#define SP_PROT_SSL3TLS1_X_CLIENTS	(SP_PROT_TLS1_X_CLIENT | SP_PROT_SSL3_CLIENT)
#define SP_PROT_SSL3TLS1_X_SERVERS	(SP_PROT_TLS1_X_SERVER | SP_PROT_SSL3_SERVER)
#define SP_PROT_SSL3TLS1_X		(SP_PROT_SSL3 | SP_PROT_TLS1_X)

#define SP_PROT_X_CLIENTS		(SP_PROT_CLIENTS | SP_PROT_TLS1_X_CLIENT | SP_PROT_DTLS1_X_CLIENT)
#define SP_PROT_X_SERVERS		(SP_PROT_SERVERS | SP_PROT_TLS1_X_SERVER | SP_PROT_DTLS1_X_SERVER )

#endif

#endif /* WINPR_SSPI_SCHANNEL_H */
