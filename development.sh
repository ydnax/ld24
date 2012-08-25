while :; do inotifywait -e MODIFY -r src SConstruct;scons debug=1;done
