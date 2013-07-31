crab_submit() {
   for i in $*; do
      [ ! -d "$i" ] && continue
      crab -submit -c $i
   done
}

crab_status() {
   if [ "x$1" == "x-v" ]; then
      shift
   else
      cmd="|grep '>>>'"
   fi
   for i in $*; do
      [ ! -d "$i" ] && continue
      do="crab -status -getoutput -c $i $cmd"
      echo $do
      $SHELL -c "$do"
   done
}

crab_resubmit() {
   for i in $*; do
      [ ! -d "$i" ] && continue
      crab -status -getoutput -c $i|grep -A 1 '>>>.*Code : [^0]'|awk '/List/ {print "crab -resubmit", $4, "-c '$i'"}';
   done | while read cmd; do
      $cmd
   done
}
