#!/usr/bin/python3

import sys, os, glob, getopt
import xml.etree.ElementTree as ET

def usage():
    print("\n")
    print("Usage information: process_svg.py -i <path/to/directory>")
    print("\n")

def main(argv):
    try:
        opts, args = getopt.getopt(argv, "i:")
    except getopt.GetoptError:
        usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            usage();
            sys.exit()
        elif opt == "-i":
            # Register the namespaces
            ET.register_namespace('', "http://www.w3.org/2000/svg")
            ET.register_namespace('xlink', "http://www.w3.org/1999/xlink")

            # Image tag attribute to replace
            imageLink = "{http://www.w3.org/1999/xlink}href"

            # Define input and output directories
            inDir = arg

            # outDir = inDir + '/out' #Uncomment to write to a different directory

            # Process svg files in the input directory
            os.chdir(inDir)

            # Count the number of files processed
            i = 0

            print("-----")

            for file in glob.glob("*.svg"):

                with open(file,'r') as f:
                    tree = ET.parse(f)

                    for node in tree.iter():

                        if node.tag.endswith('image'):
                            filename = node.attrib.get('id') + '.png';
                            # print filename
                            node.set(imageLink, filename)

                tree.write(inDir+'/'+file, encoding='UTF-8', xml_declaration=True)
                i += 1
                print ("Processed " + file)
                # End of file processing

            print("-----")
            print("Finished: " +  str(i) + " files processed.")

if __name__ == "__main__":
    main(sys.argv[1:])
