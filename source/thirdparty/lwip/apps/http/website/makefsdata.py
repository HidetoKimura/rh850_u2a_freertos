#!/usr/bin/python3

import os
script_dir = os.path.dirname(os.path.abspath(__file__))
output_file = script_dir+"/" + "fsdata.c"
with open(output_file, "w") as OUTPUT:
    
    
    fs_dir = os.path.join(script_dir, 'fs')
    file_list = []
    file_name_list = []
    for root, dirs, files in os.walk(fs_dir):
        for name in files:
            file_path = os.path.join(root, name)
            # Do not include files in CVS directories or backup files.
            if "CVS" in file_path or "~" in file_path:
                continue
            file_list.append(file_path)
            file_name_list.append(name)

    fvars = []
    files = []
    
    for file in file_list:
        headers = []

        if "404" in file:
            headers.append("HTTP/1.0 404 File not found\r\n")
        else:
            headers.append("HTTP/1.0 200 OK\r\n")

        headers.append("Server: lwIP/pre-0.6 (http://www.sics.se/~adam/lwip/)\r\n")

        if file.endswith(".html"):
            headers.append("Content-type: text/html\r\n")
        elif file.endswith(".gif"):
            headers.append("Content-type: image/gif\r\n")
        elif file.endswith(".css"):
            headers.append("Content-type: text/css\r\n")
        elif file.endswith(".png"):
            headers.append("Content-type: image/png\r\n")
        elif file.endswith(".woff"):
            headers.append("Content-type: application/font-woff\r\n")
        elif file.endswith(".woff2"):
            headers.append("Content-type: application/font-woff2\r\n")
        elif file.endswith(".ttf"):
            headers.append("Content-type: application/x-font-ttf\r\n")
        elif file.endswith(".svg"):
            headers.append("Content-type: image/svg+xml\r\n")
        elif file.endswith(".eot"):
            headers.append("Content-type: application/vnd.ms-fontobject\r\n")
        elif file.endswith(".otf"):
            headers.append("Content-type: application/x-font-opentype\r\n")
        elif file.endswith(".jpg"):
            headers.append("Content-type: image/jpeg\r\n")
        elif file.endswith(".class"):
            headers.append("Content-type: application/octet-stream\r\n")
        elif file.endswith(".ram"):
            headers.append("Content-type: audio/x-pn-realaudio\r\n")
        else:
            headers.append("Content-type: text/plain\r\n")

        headers.append("\r\n")

        # Read file content
        with open(file, "rb") as f:
            content = f.read()

        # Combine headers and content
        if not file.endswith(".plain") and "cgi" not in file:
            combined_content = "".join(headers).encode() + content
        else:
            combined_content = content

        # Prepare variable names
        fvar = file.replace(".", "").replace("/", "_")
        filename = os.path.basename(file)
        fvar = filename.replace(".", "_").replace("/", "_")
        OUTPUT.write(f"static const unsigned char data_{fvar}[] = {{\n")
        OUTPUT.write(f"\t/* {filename} */\n\t")

        # Write file name as hex values
        file_name_bytes = "/".encode() + filename.encode()
        OUTPUT.write(", ".join(f"0x{b:02x}" for b in file_name_bytes))
        OUTPUT.write(", 0,\n")

        # Write content as hex values
        for i in range(0, len(combined_content), 10):
            line_bytes = combined_content[i:i+10]
            OUTPUT.write("\t")
            OUTPUT.write(", ".join(f"0x{b:02x}" for b in line_bytes))
            OUTPUT.write(",\n")

        OUTPUT.write("};\n\n")
        fvars.append(fvar)
        files.append(file)

    for i, fvar in enumerate(fvars):
        file = files[i]
        prevfile = "NULL" if i == 0 else f"file_{fvars[i - 1]}"
        filename_length = len(file_name_list[i].encode()) + 2
        OUTPUT.write(f"const struct fsdata_file file_{fvar}[] = {{")
        OUTPUT.write(f"{prevfile}, data_{fvar}, ")
        OUTPUT.write(f"data_{fvar} + {filename_length}, ")
        OUTPUT.write(f"sizeof(data_{fvar}) - {filename_length}}};\n\n")

    OUTPUT.write(f"#define FS_ROOT file_{fvars[-1]}\n\n")
    OUTPUT.write(f"#define FS_NUMFILES {len(fvars)}\n")
