#!/bin/bash

arg="$1"
dir="$2"
if [ -z $arg ]; then
	echo "ERROR: class not specified"
	exit 1
fi
if [ -z $dir ]; then
	echo "ERROR: subdirectory not specified"
	exit 1
fi

if [ -f $dir ]; then
	echo "ERROR: please make sure $dir exists"
	exit 1
fi
file=$(find "$HOME/src/git/Sonic Mania/Sonic-Mania-Decompilation/SonicMania/" -maxdepth 12 -name "$arg.h")
if [ -z "$file" ]; then
	echo "ERROR: file $arg.c not found"
	exit 1
fi


output_h=hypermania/Objects/Boilerplate/$dir/$arg.h
output_c=hypermania/Objects/Boilerplate/$dir/$arg.c
if [ -f $output_h ]; then
	rm $output_h
fi
if [ -f $output_c ]; then
	rm $output_c
fi

echo "#ifndef OBJ_${arg^^}_H"                         >> $output_h
echo "#define OBJ_${arg^^}_H"                         >> $output_h
echo ""                                               >> $output_h
echo "#include \"GameAPI/Game.h\""                    >> $output_h
echo ""                                               >> $output_h
echo "typedef struct {"                               >> $output_h
awk "/struct Object$arg/{f=1;next} /};/{f=0} f" "$file" >> $output_h
echo "} Object$arg;"                                  >> $output_h
echo ""                                               >> $output_h
echo "typedef struct {"                               >> $output_h
awk "/struct Entity$arg/{f=1;next} /};/{f=0} f" "$file" >> $output_h
echo "} Entity$arg;"                                  >> $output_h
echo ""                                               >> $output_h
echo "extern Object$arg *$arg;"                       >> $output_h
echo ""                                               >> $output_h
echo "#endif //! OBJ_${arg^^}_H"                      >> $output_h

echo "#include \"$arg.h\""                            >> $output_c
echo ""                                               >> $output_c
echo "Object$arg *$arg;"                              >> $output_c
