# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef bytes str_to_bytes(object s):
  if s is None or isinstance(s, bytes):
    return s
  elif isinstance(s, unicode):
    return s.encode('ascii')
  else:
    raise TypeError('Expected bytes, str, or unicode, not {}'.format(type(s)))

cdef bytes _encode(object string_or_none):
  if string_or_none is None:
    return b''
  elif isinstance(string_or_none, (bytes,)):
    return <bytes>string_or_none
  elif isinstance(string_or_none, (unicode,)):
    return string_or_none.encode('utf8')
  else:
    raise TypeError('Expected str, not {}'.format(type(string_or_none)))

cdef str _decode(bytes bytestring):
    if isinstance(bytestring, (str,)):
        return <str>bytestring
    else:
        try:
            return bytestring.decode('utf8')
        except UnicodeDecodeError:
            _LOGGER.exception('Invalid encoding on %s', bytestring)
            return bytestring.decode('latin1')
