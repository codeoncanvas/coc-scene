#!/usr/bin/python3

import sys, os, glob, getopt
import xml.etree.ElementTree as ET

def getPosition(node, parent):
    position = -1
    for item in parent.iter():
        if item.attrib.get('id') == node.attrib.get('id'):
            break
        else:
            position = position + 1
    return position

def processFile(filePath):
    # Image tag attribute to replace
    imageTag = "{http://www.w3.org/2000/svg}image"
    imageLink = "{http://www.w3.org/1999/xlink}href"

    # Read the input tree
    tree = ET.parse(filePath)
    root = tree.getroot()

    # Create a parent dictionary for use, we need this for slices
    parent_map = dict((c, p) for p in tree.getiterator() for c in p)

    for node in tree.iter():
        if node.tag.endswith('image'):
            parent = parent_map[node]
            parentID = parent.attrib.get('id')
            grandParent = parent_map[parent]
            grandParentID = grandParent.attrib.get('id')
            if 'id' in node.attrib:
                filename = node.attrib.get('id') + '.png';
                node.set(imageLink, filename)
            else:
                filename = parent.attrib.get('id') + '.png'
                transformAttribute = parent.attrib.get('transform')[10:-1]
                values = transformAttribute.split(', ', 1)
                node.set('x', values[0])
                node.set('y', values[1])
                node.set('id', parent.attrib.get('id'))
                node.set(imageLink, filename)
                nodeIndex = getPosition(parent, grandParent)
                grandParent.insert(nodeIndex,node)
                grandParent.remove(parent)
    tree.write(filePath, encoding='UTF-8', xml_declaration=True)
    print ("Processed " + filePath)

def usage():
    print("\n")
    print("Script accommodates slices and image groups.")
    print("Built for Waterfall assets, but should work everywhere.")
    print("\n")
    print("Usage information:")
    print("process_svg.py -i <path/to/directory>")
    print("process_svg.py -f <path/to/file>")
    print("\n")

def main(argv):
    try:
        opts, args = getopt.getopt(argv, "f:i:")
    except getopt.GetoptError:
        usage()
        sys.exit(2)

    for opt, arg in opts:
        # Register the namespaces
        ET.register_namespace('', "http://www.w3.org/2000/svg")
        ET.register_namespace('xlink', "http://www.w3.org/1999/xlink")

        # Image tag attribute to replace
        imageTag = "{http://www.w3.org/2000/svg}image"
        imageLink = "{http://www.w3.org/1999/xlink}href"

        if opt == '-h':
            usage()
            sys.exit()
        elif opt == "-f":
            processFile(arg)

        elif opt == "-i":
            # Define input and output directories
            print arg
            inDir = arg

            # outDir = inDir + '/out' #Uncomment to write to a different directory

            # Process svg files in the input directory
            os.chdir(inDir)

            # Count the number of files processed
            i = 0

            print("-----")

            for file in glob.glob("*.svg"):

                with open(file,'r') as f:
                    processFile(file)

                # ET.ElementTree(top).write(inDir+'/'+file, encoding='UTF-8', xml_declaration=True)
                i += 1
                # End of file processing

            print("-----")
            print("Finished: " +  str(i) + " files processed.")

if __name__ == "__main__":
    main(sys.argv[1:])
