#----------------------------------------------------------------------
# Name:         updateBuild.py
# Author:       (c) 2004-2008 Jory Stone <jcsston@jory.info>
# Licence:      GPL license
#----------------------------------------------------------------------
"""Custom Build Step Python script for compiling munin-node-win32
GPL license - (c) 2004-2008 Jory Stone <jcsston@jory.info>

Usage: updateBuild.py -v [-i file] [-o file]

 -v         Verbose output
 -h         This usage help
 -i file    Input version template resource file to read in
 -o file    Output filename for version resource file
"""
import sys
import getopt
import subprocess

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "vhi:o:", ["verbose", "help", "input=", "output="])
    except getopt.GetoptError, msg:
        print msg
        print __doc__,
        return 1

    for o, a in opts:
        if o in ("-v", "--verbose"):
            verbose = True
        elif o in ("-i", "--input"):
            template_filename = a
        elif o in ("-o", "--output"):
            resource_filename = a                
        elif o in ("-h", "--help"):
            print __doc__,
            return 1
            
    if template_filename is None:
        raise ("Error: Template Filename is required.\n" + __doc__)

    if resource_filename is None:
        raise ("Error: Output Filename is required.\n" + __doc__)

        
    template_file = open(template_filename, "r")        

    template_file.seek(0)

    # Go through the file line-by-line
    template_file_lines = template_file.readlines()
    for template_file_index, template_file_line in enumerate(template_file_lines):
        if (template_file_line.find("FILEVERSION") > -1):
            # Extract the current version
            version_str = template_file_line.replace("FILEVERSION", "")
            version_str = version_str.strip()
            version_str = version_str.split(",")
            version_major = int(version_str[0])
            version_minor = int(version_str[1])
            version_build = int(version_str[3])
            version_build = subprocess.Popen(["svnversion", "-n"], stdout=subprocess.PIPE).communicate()[0].strip("M").split(":")[0]
            print "Major: " + str(version_major) + " Minor: " + str(version_minor) + " Revision Number: " + str(version_build)            
            template_file_lines[template_file_index] = " FILEVERSION " + str(version_major) + ", " + str(version_minor) + ", 0, " + str(version_build) + "\n"

        elif (template_file_line.find("FileVersion") > -1):
            if version_build < 0:
                raise "Error: Version not found!!!"
            template_file_lines[template_file_index] = "            VALUE \"FileVersion\", \"" + str(version_major) + ", " + str(version_minor) + ", 0, " + str(version_build) + "\\0\" \n"

        elif (template_file_line.find("PRODUCTVERSION") > -1):
            if version_build < 0:
                raise "Error: Version not found!!!"
            template_file_lines[template_file_index] = " PRODUCTVERSION " + str(version_major) + ", " + str(version_minor) + ", 0, " + str(version_build) + "\n"
            
        elif (template_file_line.find("ProductVersion") > -1):
            if version_build < 0:
                raise "Error: Version not found!!!"
            template_file_lines[template_file_index] = "            VALUE \"ProductVersion\", \"" + str(version_major) + ", " + str(version_minor) + ", 0, " + str(version_build) + "\\0\" \n"
            
    # Open the file for writing
    output_file = open(resource_filename, "w")
    output_file.writelines(template_file_lines)
    
if __name__ == '__main__':
    main();