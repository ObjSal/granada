/**
  * Copyright (c) <2016> granada <afernandez@cookinapps.io>
  *
  * This source code is licensed under the MIT license.
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  *
  * Session that allows to store and retrieve string values.
  * Uses cache/map_cache_driver.h
  *
  */

#pragma once
#include "session.h"
#include "map_roles.h"
#include "granada/defaults.h"
#include "shared_map_session_handler.h"
#include "granada/cache/map_cache_driver.h"

namespace granada{
  namespace http{
    namespace session{
      class StorageSession : public Session
      {
        public:

          /**
           * Constructors
           */
          StorageSession();
          StorageSession(web::http::http_request &request,web::http::http_response &response);
          StorageSession(web::http::http_request &request);
          StorageSession(const std::string& token);

          // override
          void set(granada::http::session::Session* session){
            (*this) = (*((granada::http::session::StorageSession*)session));
            roles_->SetSession(this);
          };

          // override
          void Update();

          // override
          std::shared_ptr<granada::http::session::Roles> roles(){ return roles_; };


          /**
           * Write session data.
           * @param key   Key or name of the data.
           * @param value Data as string.
           */
          void Write(const std::string& key, const std::string& value);


          /**
           * Read session data.
           * @param  key Key or name of the data.
           * @return     Data as string.
           */
          const std::string Read(const std::string& key);


          /**
           * Destroy session data with given key.
           * @param key Data key or name.
           */
          void Destroy(const std::string& key);

        private:

          granada::http::session::SessionHandler* session_handler(){ return session_handler_.get(); };

          /**
           * Hanlder of the sessions lifetime, and where all the application sessions are stored.
           */
          static std::unique_ptr<granada::http::session::SessionHandler> session_handler_;

          /**
           * Loads the properties as session_clean_extra_timeout_.
           */
          void LoadProperties();

          /**
           * Manager of the roles of the session and its properties
           */
          std::shared_ptr<granada::http::session::Roles> roles_;

          /**
           * Manager of the storage, and contains
           * the data stored.
           */
          granada::cache::MapCacheDriver cache_;


          /**
           * Used for determining if the session is garbage.
           * In case the session is timed out since x seconds indicated
           * in the "session_clean_extra_timeout" property
           * If no property indicated, it will take default_numbers::session_session_clean_extra_timeout.
           */
          long session_clean_extra_timeout_;

      };
    }
  }
}
