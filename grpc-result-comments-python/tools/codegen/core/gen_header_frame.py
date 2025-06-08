Here's the commented version of the code:

```python
#!/usr/bin/env python3

# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Read from stdin a set of colon separated http headers:
   :path: /foo/bar
   content-type: application/grpc
   Write a set of strings containing a hpack encoded http2 frame that
   represents said headers."""

import argparse
import json
import sys

def append_never_indexed(payload_line, n, count, key, value, value_is_huff):
    """Append a never-indexed header field representation to payload_line.
    
    Args:
        payload_line: List to append the encoded header to
        n: Current header index
        count: Total number of headers
        key: Header name
        value: Header value
        value_is_huff: Boolean indicating if value is Huffman encoded
    """
    payload_line.append(0x10)  # Never-indexed field representation
    assert len(key) <= 126  # HPACK limits string length to 126
    payload_line.append(len(key))  # Append key length
    payload_line.extend(ord(c) for c in key)  # Append key characters
    assert len(value) <= 126  # HPACK limits string length to 126
    # Append value length with Huffman flag if needed
    payload_line.append(len(value) + (0x80 if value_is_huff else 0))
    payload_line.extend(value)  # Append value bytes

def append_inc_indexed(payload_line, n, count, key, value, value_is_huff):
    """Append an incremental indexed header field representation to payload_line.
    
    Args:
        payload_line: List to append the encoded header to
        n: Current header index
        count: Total number of headers
        key: Header name
        value: Header value
        value_is_huff: Boolean indicating if value is Huffman encoded
    """
    payload_line.append(0x40)  # Incremental indexed field representation
    assert len(key) <= 126
    payload_line.append(len(key))  # Append key length
    payload_line.extend(ord(c) for c in key)  # Append key characters
    assert len(value) <= 126
    # Append value length with Huffman flag if needed
    payload_line.append(len(value) + (0x80 if value_is_huff else 0))
    payload_line.extend(value)  # Append value bytes

def append_pre_indexed(payload_line, n, count, key, value, value_is_huff):
    """Append a pre-indexed header field representation to payload_line.
    
    Args:
        payload_line: List to append the encoded header to
        n: Current header index
        count: Total number of headers
        key: Header name
        value: Header value (unused for pre-indexed)
        value_is_huff: Boolean indicating if value is Huffman encoded
    """
    assert not value_is_huff  # Pre-indexed fields can't be Huffman encoded
    # Append index with pre-indexed flag (0x80)
    payload_line.append(0x80 + 61 + count - n)

def esc_c(line):
    """Escape bytes for C string representation.
    
    Args:
        line: List of bytes to escape
        
    Returns:
        String containing C-style escaped bytes
    """
    out = '"'
    last_was_hex = False
    for c in line:
        if 32 <= c < 127:  # Printable ASCII range
            if c in hex_bytes and last_was_hex:
                out += '""'
            if c != ord('"'):
                out += chr(c)
            else:
                out += '\\"'
            last_was_hex = False
        else:
            out += "\\x%02x" % c  # Escape non-printable as hex
            last_was_hex = True
    return out + '"'

def output_c(payload_bytes):
    """Output payload as C-style escaped strings.
    
    Args:
        payload_bytes: List of byte lists representing the payload
    """
    for line in payload_bytes:
        print((esc_c(line)))

def output_hex(payload_bytes):
    """Output payload as C-style hex array.
    
    Args:
        payload_bytes: List of byte lists representing the payload
    """
    all_bytes = []
    for line in payload_bytes:
        all_bytes.extend(line)
    print(("{%s}" % ", ".join("0x%02x" % c for c in all_bytes)))

def output_hexstr(payload_bytes):
    """Output payload as continuous hex string.
    
    Args:
        payload_bytes: List of byte lists representing the payload
    """
    all_bytes = []
    for line in payload_bytes:
        all_bytes.extend(line)
    print(("%s" % "".join("%02x" % c for c in all_bytes)))

# Compression methods mapping
_COMPRESSORS = {
    "never": append_never_indexed,
    "inc": append_inc_indexed,
    "pre": append_pre_indexed,
}

# Output format methods mapping
_OUTPUTS = {
    "c": output_c,
    "hex": output_hex,
    "hexstr": output_hexstr,
}

# Parse command line arguments
argp = argparse.ArgumentParser("Generate header frames")
argp.add_argument(
    "--set_end_stream", default=False, action="store_const", const=True,
    help="Set END_STREAM flag in header frame"
)
argp.add_argument(
    "--no_framing", default=False, action="store_const", const=True,
    help="Omit HTTP/2 frame header"
)
argp.add_argument(
    "--compression", choices=sorted(_COMPRESSORS.keys()), default="never",
    help="Header compression method"
)
argp.add_argument(
    "--huff", default=False, action="store_const", const=True,
    help="Use Huffman encoding for values"
)
argp.add_argument(
    "--output", default="c", choices=sorted(_OUTPUTS.keys()),
    help="Output format"
)
args = argp.parse_args()

# Process input headers
vals = []
for line in sys.stdin:
    line = line.strip()
    if line == "":  # Skip empty lines
        continue
    if line[0] == "#":  # Skip comments
        continue
    # Split into key-value pairs
    key_tail, value = line[1:].split(":")
    key = (line[0] + key_tail).strip()
    value = value.strip().encode("ascii")
    if args.huff:  # Apply Huffman encoding if requested
        from hpack.huffman import HuffmanEncoder
        from hpack.huffman_constants import REQUEST_CODES
        from hpack.huffman_constants import REQUEST_CODES_LENGTH

        value = HuffmanEncoder(REQUEST_CODES, REQUEST_CODES_LENGTH).encode(
            value
        )
    vals.append((key, value))

# Generate payload
payload_bytes = []
if not args.no_framing:
    payload_bytes.append([])  # Reserve space for frame header
payload_len = 0
n = 0
for key, value in vals:
    payload_line = []
    _COMPRESSORS[args.compression](
        payload_line, n, len(vals), key, value, args.huff
    )
    n += 1
    payload_len += len(payload_line)
    payload_bytes.append(payload_line)

# Add HTTP/2 frame header if needed
if not args.no_framing:
    flags = 0x04  # END_HEADERS flag
    if args.set_end_stream:
        flags |= 0x01  # Add END_STREAM flag
    payload_bytes[0].extend(
        [
            (payload_len >> 16) & 0xFF,  # Length (24 bits)
            (payload_len >> 8) & 0xFF,
            (payload_len) & 0xFF,
            0x01,  # Type (HEADERS)
            flags,  # Flags
            0x00,  # R bit + 31-bit stream identifier
            0x00,
            0x00,
            0x01,  # Stream ID 1
        ]
    )

# Characters that might need special handling in C output
hex_bytes = [ord(c) for c in "abcdefABCDEF0123456789"]

# Generate output in requested format
_OUTPUTS[args.output](payload_bytes)
```