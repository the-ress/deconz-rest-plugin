/*
 * Copyright (c) 2018 dresden elektronik ingenieurtechnik gmbh.
 * All rights reserved.
 *
 * The software in this package is published under the terms of the BSD
 * style license a copy of which has been included with this distribution in
 * the LICENSE.txt file.
 *
 */

#include "de_web_plugin.h"
#include "de_web_plugin_private.h"

/*! Capabilities REST API broker.
    \param req - request data
    \param rsp - response data
    \return REQ_READY_SEND
            REQ_NOT_HANDLED
 */
int DeRestPluginPrivate::handleCapabilitiesApi(const ApiRequest &req, ApiResponse &rsp)
{
    // GET /api/<apikey>/capabilities
    if ((req.path.size() == 3) && (req.hdr.method() == "GET"))
    {
        return getCapabilities(req, rsp);
    }

    return REQ_NOT_HANDLED;
}

/*! GET /api/<apikey>/info/timezones
    \return REQ_READY_SEND
            REQ_NOT_HANDLED
 */
int DeRestPluginPrivate::getCapabilities(const ApiRequest &req, ApiResponse &rsp)
{
    Q_UNUSED(req);

    QVariantMap tzs;
    tzs["values"] = getTimezones();
    rsp.map["timezones"] = tzs;

    rsp.httpStatus = HttpStatusOk;
    return REQ_READY_SEND;
}
