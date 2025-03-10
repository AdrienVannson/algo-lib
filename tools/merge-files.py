import re
import os.path

FIRST_FILE = 'main.cpp'

def lines_of_file(fn):
    try:
        with open(fn, 'r') as f:
            return [l.rstrip('\n') for l in f.readlines()] # Remove \n at the end of each line
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


""" Compute the files that will be included in the final file """
files_to_include = set()
words = set()

# A list of (file to include, words needed). If words needed is None, no word is needed
pending_includes = [(get_full_path(FIRST_FILE)[1], None)]

while len(pending_includes):
    success = False

    for i in range(len(pending_includes)):
        if pending_includes[i][1] is None:
            success = True
        else:
            for w in pending_includes[i][1]:
                if w in words:
                    success = True

        if success:
            file = pending_includes.pop(i)[0]

            if file not in files_to_include:
                files_to_include.add(file)

                # Add the .cpp if needed
                if file[-4:] == '.hpp':
                    source_file = file[:-4] + '.cpp'
                    if os.path.exists(source_file):
                        pending_includes.append((source_file, None))

                for line in lines_of_file(file):
                    if re.match("^#include \"*\"", line): # Add the include to the list
                        words_needed = None
                        if ' // ONLY_IF ' in line:
                            line, words_needed = line.split(' // ONLY_IF ')
                            words_needed = words_needed.split()

                        folder, path = get_full_path(re.sub("^\\#include \"(.+)\"$", "\\1", line))
                        if folder not in path_folders:
                            path_folders.append(folder)

                        if path not in files_to_include:
                            pending_includes.append((path, words_needed))

                    else: # Add the words to the dictionnary
                        for w in re.split(r"\W", line):
                            if len(w):
                                words.add(w)

            break

    if not success:
        break


""" Generate the output file """
output = []

# Contains the remaining lines to parse. The last line is the next one to be parsed
pending = list(reversed(lines_of_file(FIRST_FILE)))

while len(pending):
    line = pending[-1]
    pending.pop()

    if re.match("^#include \"*\"", line) and ' // IGNORE' not in line:
        if ' // ONLY_IF ' in line:
            line = line.split(' // ONLY_IF ')[0]

        relative_path = re.sub("^\\#include \"(.+)\"$", "\\1", line)
        folder, file = get_full_path(relative_path)

        if file == '':
            print("Can't find file", relative_path)

        # Check if the file must be included
        elif file in files_to_include:
            files_to_include.remove(file)

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


""" Remove header guards """
new_output = []
for l in output:
    if not re.match("^#ifndef .*_HPP$", l) and not re.match("^#define .*_HPP$", l) and not re.match("^#endif .*_HPP", l):
        new_output.append(l)
output = new_output


""" Remove #pragma once """
new_output = []
for l in output:
    if l != "#pragma once":
        new_output.append(l)
output = new_output


""" Move includes and "using namesace" to the begin of the file """
new_output = []
begin = set()
for l in output:
    if re.match("^#include <", l) or l == "using namespace std;":
        begin.add(l)
    else:
        new_output.append(l)
output = sorted(list(begin)) + new_output


""" Remove consecutive empty lines """
is_last_line_empty = True
new_output = []
for l in output:
    if len(l) > 0 or not is_last_line_empty:
        new_output.append(l)
    is_last_line_empty = len(l) == 0
output = new_output


""" Write output.cpp """
with open('output.cpp', 'w') as output_file:
    for l in output:
        output_file.write(l + '\n')
