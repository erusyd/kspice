#! /bin/sh -
#
# For generating PC 3.5" disks on a UNIX machine;  assumes that the
# "pc-to-unix/unix-to-pc" package "mtools" (by Emmet P. Gray) is in your path.
# Modify the "mwrite" command to return a non-zero exit statis when the disk
# is full.  The script doesn't depend on disk capacity.
#
# Cd into the directory to back, and swap disks when it asks.
# Note: the disks are not automatically formatted.
#

# Variable initialization
directory=.
echo=
dknum=0
direct="."
dos2dos=0
newdir=""
stage2=0
version=""
preload=/tmp/preload.$$
{ for x in 0 1 2 3 4 5 6 7 8 9; do
	echo "abcdefgh" | sed 's/./&&&&&&&&&&/g'
	echo "zyxwvuts" | sed 's/./&&&&&&&&&&/g'
  done } > /tmp/JUNK

# Arg processing
while test "$#" -ne 0; do
	case "$1" in
	-2)
		stage2=1
		preload=/tmp/preload
		echo "Using file $preload for disk #$2 and on"
		dknum=`expr "$2" - 1`
		shift
		;;
	-d)
		echo "DEBUG mode"
		echo=echo
		;;
	*)
		version=$1;
		;;
	esac
	shift
done

if test "${version}" = ""; then
	echo "usage: $0 <version id>"
	exit 1
fi

if test "$stage2" -ne 1; then
	echo "Scanning files in $directory"
	find "$directory" -print  > "$preload"
	echo "Scan done; executing stage 2"
	echo ''
else
	echo "File list pre-scanned"
fi
echo ''

trap "echo Interrupt!; exit 99" 2

newdisk=y
xxxx=y
cat "$preload" | \
	while read xname; do
		xxxx=n
		name=`echo "$xname" | sed 's/^\.\///'`
		#echo "$name $size"

		if test "$name" = ""; then
			continue
		fi

		if test "$name" = "."; then
			continue
		fi

		if test "$newdisk" = "y"; then
			# New Disk
			dknum=`expr "$dknum" + 1`
			rm -f /tmp/INSTALL
			{ echo "IF EXIST %1\\UNLOAD.BAT GOTO OK";
			  echo 'ECHO "usage: %0 <drive from>"';
			  echo "GOTO END";
			  echo ":OK"; }		> /tmp/INSTALL
			echo Insert disk "$dknum" and hit return
			{ read space; } <&2
			# Initial write of UPDATE.BAT reserves space
			mkdfs -h -l "Spice${version}-$dknum"
			$echo mcopy -t /tmp/JUNK a:UNLOAD.BAT

			# Create directories on the new disk
			if test ! X"$direct" = X.; then
				eval `makedirs "$direct" | \
					sed -e 's/^/$echo mmd /' -e 's/$/;/'`
			fi
			# Copy command for extra files XXX
			echo "COPY %1\*.* ." >> /tmp/INSTALL
			if test ! "$direct" = "."; then
				makedirs "$direct" | \
					sed -e 's/.*/COPY %1\\&\\*.* &/' \
						-e 's/\//\\/g' \
					>> /tmp/INSTALL
			fi
			if test X"$oldfile" != X""; then
				echo "$oldfile -- "
				if $echo mcopy -tm "$oldfile" a:"$oldfile"; then
					echo "ok"
				else
					echo \
				"Error! $oldfile not copied, disk $dknum"
					exit 1
				fi
				oldfile=""
			fi
			newdisk=n
		fi

		if test -d "$name"; then
			# mkdir command in the install script
			makedirs "$name" "$direct" | \
				sed -e 's/^/MKDIR /' -e 's/\//\\/g' \
				>> /tmp/INSTALL
			makedirs "$name" "$direct" | \
				sed -e 's/.*/COPY %1\\&\\*.* &/' \
						-e 's/\//\\/g' \
				>> /tmp/INSTALL
			direct="$name"
			if test ! "$newdir" = ""; then
				$echo mmd "$newdir"
			fi
			newdir="$direct"
		else
			# Add a new directory if necessary
			if test "$newdir" != ""; then
				$echo mmd "$newdir"
				newdir=""
			fi

			# Copy file, check to see if space full
			echo -n "$name -- "
			if $echo mcopy -tm "$name" a:"$name"; then
				echo OK;
			else
				# Space full, re-write install script
				echo "failed"
				echo "ENDDISK"
				echo "DEL UNLOAD.BAT"	>> /tmp/INSTALL
				echo ":END"		>> /tmp/INSTALL
				$echo mdel UNLOAD.BAT
				$echo mcopy -tm /tmp/INSTALL \
					a:UNLOAD.BAT
				rm /tmp/INSTALL
				oldfile="$name"
				newdisk=y
			fi
		fi
	done

# Clean up last disk
if test -r /tmp/INSTALL; then
	echo ":END"	>> /tmp/INSTALL
	$echo mdel UNLOAD.BAT
	$echo mcopy -tm /tmp/INSTALL a:UNLOAD.BAT
fi

echo "ALL DONE!"
