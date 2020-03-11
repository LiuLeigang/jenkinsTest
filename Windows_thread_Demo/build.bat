set path = %path%;C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin

msbuild /p:Configuration=Release
if %errorlevel% neq 0 (
cd
echo "error!"
pause
)

del /s /q *.pdb

