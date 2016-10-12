incoming = raw_input("Enter data")
print "%s" % incoming

# parse the data
moduleID = incoming[0]
temp = incoming[1:4]
light = incoming[4:]

print "id:%s,  temp:%s,  light:%s" % (moduleID, temp, light)

tempFile = moduleID + "_temp"
lightFile = moduleID + "_light"

print "temp file: %s,  light file: %s " % (tempFile, lightFile)

tempfile = open('temp/%s' % tempFile, 'a')
lightfile = open('light/%s' % lightFile, 'a')

tempfile.write("%s\n" % temp)
lightfile.write("%s\n" % light)

tempfile.close()
lightfile.close()
