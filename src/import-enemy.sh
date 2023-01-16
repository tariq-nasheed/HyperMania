#!/bin/bash
# TODO very unoptimized and messy, fix this!!!!!!!!!!!!!!!!

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
file_h=$(find "$HOME/src/git/Sonic Mania/Sonic-Mania-Decompilation/SonicMania/" -maxdepth 12 -name "$arg.h")
if [ -z $file_h ]; then
	echo "ERROR: file $arg.h not found"
	exit 1
fi
file_c=$(find "$HOME/src/git/Sonic Mania/Sonic-Mania-Decompilation/SonicMania/" -maxdepth 12 -name "$arg.c")
if [ -z $file_c ]; then
	echo "ERROR: file $arg.c not found"
	exit 1
fi


# .h file construction ---------------------------------------------------------
output_h=hypermania/Objects/Boilerplate/$dir/$arg.h

if [ -f $output_h ]; then
	rm $output_h
fi

echo "#ifndef OBJ_${arg^^}_H"                           >> $output_h
echo "#define OBJ_${arg^^}_H"                           >> $output_h
echo ""                                                 >> $output_h
echo "#include \"GameAPI/Game.h\""                      >> $output_h
echo ""                                                 >> $output_h
echo "typedef struct {"                                 >> $output_h
awk "/struct Object$arg/{f=1;next} /};/{f=0} f" $file_h >> $output_h
echo "} Object$arg;"                                    >> $output_h
echo ""                                                 >> $output_h
echo "typedef struct {"                                 >> $output_h
awk "/struct Entity$arg/{f=1;next} /};/{f=0} f" $file_h >> $output_h
echo "} Entity$arg;"                                    >> $output_h
echo ""                                                 >> $output_h
echo "extern Object$arg *$arg;"                         >> $output_h
echo ""                                                 >> $output_h

func=$(awk '/(void)/ {f=$2; next} /BadnikBreak/ { if (lf==f) next; print f; lf=f }' $file_c)
func=${func::-6}
echo "collision function found: "$func

echo "void "$arg"_EnemyInfoHook(void);"             >> $output_h
awk '/(void)/ {f=$2; next} /'$func'/ { if (lf==f) next; print f; lf=f }' $file_c | while read line; do
	echo "state found: "${line::-6}
	echo "extern void (*"${line::-6}")(void);"  >> $output_h
done
echo ""                           >> $output_h
echo "#endif //! OBJ_${arg^^}_H"  >> $output_h


# .c file construction ---------------------------------------------------------
output_c=hypermania/Objects/Boilerplate/$dir/$arg.c

if [ -f $output_c ]; then
	rm $output_c
fi

echo "#include \"$arg.h\""  >> $output_c
echo ""                     >> $output_c
echo "Object$arg *$arg;"    >> $output_c

awk '/(void)/ {f=$2; next} /'$func'/ { if (lf==f) next; print f; lf=f }' $file_c | while read line; do
	echo "void (*"${line::-6}")(void);"         >> $output_c
done
echo "" >> $output_c

hitbox=$(awk '/hitbox/ { print $0; exit 0 }' $file_h)
hitbox="${hitbox:11}"
hitbox="${hitbox::-1}"
echo "hitbox found: "$hitbox

iterator=0
echo "void "$arg"_EnemyInfoHook(void) {"                      >> $output_c
echo "	Mod.Super("$arg"->classID, SUPER_STAGELOAD, NULL);"   >> $output_c
echo "	EnemyDefs[EnemyInfoSlot].classID = "$arg"->classID;"  >> $output_c
echo "	EnemyDefs[EnemyInfoSlot].animal = true;"              >> $output_c
awk '/(void)/ {f=$2; next} /'$func'/ { if (lf==f) next; print f; lf=f }' $file_c | while read line; do
	echo "	EnemyDefs[EnemyInfoSlot].states["$iterator"].func = "${line::-6}";"         >> $output_c
	echo "	EnemyDefs[EnemyInfoSlot].states["$iterator"].hitbox = &"$arg"->"$hitbox";"  >> $output_c
	iterator=$((++iterator))
done
echo "	++EnemyInfoSlot;" >> $output_c
echo "}"                  >> $output_c


# Enemy.h/Enemy.c shit ---------------------------------------------------------
enemy_h=hypermania/Objects/Enemy.h
enemy_c=hypermania/Objects/Enemy.c

sed "/#define HOOK_ENEMY_OBJECTS/a\  REGISTER_ENEMY($arg); \\\\" $enemy_h  > $enemy_h.tmp
mv $enemy_h.tmp $enemy_h
awk '/(void)/ {f=$2; next} /'$func'/ { if (lf==f) next; print f; lf=f }' $file_c | while read line; do
	sed "/#define IMPORT_ENEMY_FUNCTIONS/a\  GET_MANIA_FUNC("${line::-6}"); \\\\" $enemy_h  > $enemy_h.tmp
	mv $enemy_h.tmp $enemy_h
done

sed "3 a #include \"Boilerplate/$dir/$arg.h\"" $enemy_h > $enemy_h.tmp
mv $enemy_h.tmp $enemy_h
sed "3 a #include \"Boilerplate/$dir/$arg.c\"" $enemy_c > $enemy_c.tmp
mv $enemy_c.tmp $enemy_c

echo "enemy imported succesfully! please manually fix any potential errors/oversights before compiling"
