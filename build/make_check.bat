cmake --build . --target tests
pushd Debug
tests.exe
popd
pause
