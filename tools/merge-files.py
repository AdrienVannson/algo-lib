import re, os.path

def lines_of_file(fn):
    try:
        with open(fn, 'r') as f:
            return [l[:-1] for l in f.readlines()] # Remove \n at the end of each line
    except:
        return []

# Folders where files to include can be located
path_folders = [os.getcwd(), '']
for i in range(int(input())):
    path_folders.append(os.path.abspath(input()))

def get_full_path(relative_path):
    for include_folder in path_folders:
        folder = os.path.realpath(include_folder + '/' + os.path.dirname(relative_path))
        file = folder + '/' + os.path.basename(relative_path)

        if os.path.exists(file):
            return folder, file
    return '', ''

# Contains the remaining lines to parse. The last line is the next one to be parsed
pending = list(reversed(lines_of_file('main.cpp')))

output = []
included_files = []

while len(pending):
    line = pending[-1]
    pending.pop()

    if re.match("^#include \"*\"", line):
        if ' // ONLY_IF ' in line:
            line = line.split(' // ONLY_IF ')[0]

        relative_path = re.sub("^\\#include \"(.+)\"$", "\\1", line)
        folder, file = get_full_path(relative_path)

        if file == '':
            print("Can't find file", relative_path)
        # Check if the file has already been included
        elif not file in included_files:
            included_files.append(file)

            # Add the folder to the path to find the next included files
            if not folder in path_folders:
                path_folders.append(folder)

            # Add the .cpp if needed
            if file[-4:] == '.hpp':
                source_file = file[:-4] + '.cpp'
                if os.path.exists(source_file):
                    pending.append('#include "' + source_file + '"')

            # Add the content of the file
            for l in reversed(lines_of_file(file)):
                pending.append(l)

    else:
        output.append(line)

# Write output.cpp
with open('output.cpp', 'w') as output_file:
    for l in output:
        output_file.write(l + '\n')
