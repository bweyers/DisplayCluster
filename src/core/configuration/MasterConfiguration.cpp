/*********************************************************************/
/* Copyright (c) 2013, EPFL/Blue Brain Project                       */
/*                     Raphael Dumusc <raphael.dumusc@epfl.ch>       */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE IS PROVIDED  BY THE  UNIVERSITY OF  TEXAS AT    */
/*    AUSTIN  ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,    */
/*    INCLUDING, BUT  NOT LIMITED  TO, THE IMPLIED  WARRANTIES OF    */
/*    MERCHANTABILITY  AND FITNESS FOR  A PARTICULAR  PURPOSE ARE    */
/*    DISCLAIMED.  IN  NO EVENT SHALL THE UNIVERSITY  OF TEXAS AT    */
/*    AUSTIN OR CONTRIBUTORS BE  LIABLE FOR ANY DIRECT, INDIRECT,    */
/*    INCIDENTAL,  SPECIAL, EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES    */
/*    (INCLUDING, BUT  NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE    */
/*    GOODS  OR  SERVICES; LOSS  OF  USE,  DATA,  OR PROFITS;  OR    */
/*    BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON ANY THEORY OF    */
/*    LIABILITY, WHETHER  IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*    (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY OUT    */
/*    OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF ADVISED  OF  THE    */
/*    POSSIBILITY OF SUCH DAMAGE.                                    */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of The University of Texas at Austin.                 */
/*********************************************************************/

#include "MasterConfiguration.h"

#include <QtXmlPatterns>

#include "log.h"

#define DEFAULT_WEBSERVICE_PORT 8888

MasterConfiguration::MasterConfiguration(const QString &filename, OptionsPtr options)
    : Configuration(filename, options)
{
    loadMasterSettings();
}

void MasterConfiguration::loadMasterSettings()
{
    QXmlQuery query;
    if(!query.setFocus(QUrl(filename_)))
    {
        put_flog(LOG_FATAL, "failed to load %s", filename_.toLatin1().constData());
        exit(-1);
    }

    QString queryResult;

    // dock start directory
    query.setQuery("string(/configuration/dock/@directory)");
    if (query.evaluateTo(&queryResult))
        dockStartDir_ = queryResult.remove(QRegExp("[\\n\\t\\r]"));
    if( dockStartDir_.isEmpty( ))
        dockStartDir_ = QDir::homePath();

    // WebService server port
    query.setQuery("string(/configuration/webservice/@port)");
    if (query.evaluateTo(&queryResult))
    {
        if (queryResult.isEmpty())
            dcWebServicePort_ = DEFAULT_WEBSERVICE_PORT;
        else
            dcWebServicePort_ = queryResult.toInt();
    }
}

const QString &MasterConfiguration::getDockStartDir() const
{
    return dockStartDir_;
}

const int MasterConfiguration::getWebServicePort() const
{
    return dcWebServicePort_;
}
