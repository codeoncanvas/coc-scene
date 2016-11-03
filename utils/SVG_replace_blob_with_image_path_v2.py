#!/usr/bin/python3

import sys, os, glob, getopt
import xml.etree.ElementTree as ET

def processFile(filePath):
    # Image tag attribute to replace
    imageTag = "{http://www.w3.org/2000/svg}image"
    imageLink = "{http://www.w3.org/1999/xlink}href"

    tree = ET.parse(filePath)
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
                    for key, value in node.attrib.iteritems():
                        root.set(key, value)
        if node.tag.endswith('}g'):
            if 'id' in node.attrib:
                if 'fill' not in node.attrib:
                    if "/" not in node.attrib.get('id'):
                        if 'transform' not in node.attrib:
                            root = ET.SubElement(root, 'g')
                            for key, value in node.attrib.iteritems():
                                root.set(key, value)
                        else:
                            imageGroup = ET.SubElement(root, 'g')
                            for key, value in node.attrib.iteritems():
                                imageGroup.set(key, value)
        if node.tag.endswith('image'):
            parent = parent_map[node]
            parentID = parent.attrib.get('id')
            grandParent = parent_map[parent]
            grandParentID = grandParent.attrib.get('id')
            if 'id' in node.attrib:
                filename = node.attrib.get('id') + '.png';
                node.set(imageLink, filename)
                if parentID == root.attrib.get('id'):
                    root.append(node)
                elif parentID == imageGroup.attrib.get('id'):
                    imageGroup.append(node)
                elif grandParentID == imageGroup.attrib.get('id'):
                    imageGroup.append(node)
            else:
                filename = parent.attrib.get('id') + '.png'
                transformAttribute = parent.attrib.get('transform')[10:-1]
                values = transformAttribute.split(', ', 1)
                node.set('x', values[0])
                node.set('y', values[1])
                node.set('id', parent.attrib.get('id'))
                node.set(imageLink, filename)
                if grandParentID == root.attrib.get('id'):
                    root.append(node)
                elif grandParentID == imageGroup.attrib.get('id'):
                    imageGroup.append(node)
    ET.ElementTree(top).write(filePath, encoding='UTF-8', xml_declaration=True)
    print ("Processed " + filePath)

def usage():
    print("\n")
    print("This is the 2nd version of the script. This will modify the SVG file to have one parent group with all the images.")
    print("Specifically for use with Waterfall assets.")
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
