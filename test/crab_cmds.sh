crab_submit() {
   for i in $*; do
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
      echo $do
      do="crab -status -getoutput -c $i $cmd"
      $SHELL -c "$do"
   done
}

crab_resubmit() {
   for i in $*; do
      crab -status -getoutput -c $i|grep -A 1 '>>>.*Code : [^0]'|awk '/List/ {print "crab -resubmit", $4, "-c '$i'"}';
   done | while read cmd; do
      $cmd
   done
}
