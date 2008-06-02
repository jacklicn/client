/*
 * libcsync -- a library to sync a directory with another
 *
 * Copyright (c) 2006-2008 by Andreas Schneider <mail@cynapses.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * vim: ft=c.doxygen ts=2 sw=2 et cindent
 */

/**
 * @file csync.h
 *
 * @brief Application developer interface for csync.
 *
 * @defgroup csyncPublicAPI csync public API
 *
 * @{
 */

#ifndef _CSYNC_H
#define _CSYNC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * csync version information
 */
#define CSYNC_VERSION_MAJOR 0
#define CSYNC_VERSION_MINOR 42
#define CSYNC_VERSION_PATCH 0
#define CSYNC_VERSION_STRING "csync version 0.42.0 alpha1"

/*
 * csync file declarations
 */
#define CSYNC_CONF_DIR ".csync"
#define CSYNC_CONF_FILE "csync.conf"
#define CSYNC_LOG_FILE "csync_log.conf"
#define CSYNC_EXCLUDE_FILE "csync_exclude.conf"
#define CSYNC_JOURNAL_FILE "csync_journal.db"
#define CSYNC_LOCK_FILE "lock"

typedef void (*csync_module_auth_callback) (char *usr, size_t usrlen, char *pwd, size_t pwlen);

/**
 * csync handle
 */
typedef struct csync_s CSYNC;

/**
 * @brief Allocate a csync context.
 *
 * @param csync  The context variable to allocate.
 *
 * @return  0 on success, less than 0 if an error occured.
 */
int csync_create(CSYNC **csync, const char *local, const char *remote);

/**
 * @brief Initialize the file synchronizer.
 *
 * This function loads the configuration, the journal and locks the client.
 *
 * @param ctx  The context to initialize.
 *
 * @return  0 on success, less than 0 if an error occured.
 */
int csync_init(CSYNC *ctx);

/**
 * @brief Update detection
 *
 * @param ctx  The context to run the update detection on.
 *
 * @return  0 on success, less than 0 if an error occured.
 */
int csync_update(CSYNC *ctx);

/**
 * @brief Reconciliation
 *
 * @param ctx  The context to run the reconciliation on.
 *
 * @return  0 on success, less than 0 if an error occured.
 */
int csync_reconcile(CSYNC *ctx);

/**
 * @brief Propagation
 *
 * @param ctx  The context to run the propagation on.
 *
 * @return  0 on success, less than 0 if an error occured.
 */
int csync_propagate(CSYNC *ctx);

/**
 * @brief Destroy the csync context
 *
 * Writes the journal, unlocks csync and frees the memory.
 *
 * @param ctx  The context to destroy.
 *
 * @return  0 on success, less than 0 if an error occured.
 */
int csync_destroy(CSYNC *ctx);

/**
 * @brief Get the csync version.
 *
 * @return  The csync version as a string.
 */
const char *csync_version(void);

int csync_add_exclude_list(CSYNC *ctx, const char *path);
char *csync_get_config_dir(CSYNC *ctx);
int csync_set_config_dir(CSYNC *ctx, const char *path);
int csync_remove_config_dir(CSYNC *ctx);
csync_module_auth_callback csync_get_module_auth_callback(CSYNC *ctx);
int csync_set_module_auth_callback(CSYNC *ctx, csync_module_auth_callback cb);
int csync_get_status(CSYNC *ctx);
int csync_set_status(CSYNC *ctx, int status);

#ifdef __cplusplus
}
#endif

/**
 * }@
 */
#endif /* _CSYNC_H */

