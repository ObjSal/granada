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
  * See granada/http/session/checkpoint.h
  *
  */
#pragma once
#include "granada/http/session/simple_session.h"
#include "granada/http/session/checkpoint.h"

namespace granada{
  namespace http{
    namespace session{
      class SimpleSessionCheckpoint : public Checkpoint
      {
        public:

          /**
           * Constructors
           */
          SimpleSessionCheckpoint(){};

          std::shared_ptr<granada::http::session::Session> check(){
            return std::shared_ptr<granada::http::session::Session>(new granada::http::session::SimpleSession());
          };

          std::shared_ptr<granada::http::session::Session> check(web::http::http_request &request,web::http::http_response &response){
            return std::shared_ptr<granada::http::session::Session>(new granada::http::session::SimpleSession(request,response));
          };

          std::shared_ptr<granada::http::session::Session> check(web::http::http_request &request){
            return std::shared_ptr<granada::http::session::Session>(new granada::http::session::SimpleSession(request));
          };

          std::shared_ptr<granada::http::session::Session> check(const std::string& token){
            return std::shared_ptr<granada::http::session::Session>(new granada::http::session::SimpleSession(token));
          };

      };
    }
  }
}
