from fabric.api import local, settings
def dev():
    with settings(warn_only=True):
        while True:
            local('scons debug=1')
            local('inotifywait -e MODIFY -r src SConstruct')

def gits():
    while True:
        local('git status')
        local('inotifywait -e MODIFY -r .')
        local('clear')