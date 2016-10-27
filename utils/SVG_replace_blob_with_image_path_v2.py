#!/usr/bin/python3

import sys, os, glob, getopt
import xml.etree.ElementTree as ET

def usage():
    print("\n")
    print("This is the 2nd version of the script. This will modify the SVG file to have one parent group with all the images.")
    print("Specifically for use with Waterfall assets.")
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
            imageTag = "{http://www.w3.org/2000/svg}image"
            imageLink = "{http://www.w3.org/1999/xlink}href"

            # Image tag attribute to replace


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
                    root = tree.getroot()
                    parent_map = dict((c, p) for p in tree.getiterator() for c in p)

                    # Create output xmltree
                    top = ET.Element('svg')
                    for key, value in root.attrib.iteritems():
                        top.set(key, value)

                    for node in tree.iter():

                        if node.tag.endswith('}g'):
                            if 'id' in node.attrib:
                                if 'fill' in node.attrib:
                                    root = ET.SubElement(top, 'g')
                                    print node.attrib
                                    for key, value in node.attrib.iteritems():
                                        root.set(key, value)

                        if node.tag.endswith('image'):
                            if 'id' in node.attrib:
                                filename = node.attrib.get('id') + '.png';
                                node.set(imageLink, filename)
                            else:
                                parent = parent_map[node]
                                filename = parent.attrib.get('id') + '.png'
                                transformAttribute = parent.attrib.get('transform')[10:-1]
                                values = transformAttribute.split(', ', 1)
                                node.set('x', values[0])
                                node.set('y', values[1])
                                node.set('id', parent.attrib.get('id'))
                                node.set(imageLink, filename)
                                parent.set('id', 'delete');
                            root.append(node)

                ET.ElementTree(top).write(inDir+'/'+file, encoding='UTF-8', xml_declaration=True)
                i += 1
                print ("Processed " + file)
                # End of file processing

            print("-----")
            print("Finished: " +  str(i) + " files processed.")

if __name__ == "__main__":
    main(sys.argv[1:])
