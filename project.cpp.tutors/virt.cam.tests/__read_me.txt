This is the preferable way of setting output and intermediate directory paths for all C++ projects being involeved in the solution:

(1) the output path 'OutDir' for all projects can be changed in Directory.Build.props for 'Win32' and 'x64' platforms appropriately;
(2) the intermediate path 'IntDir' for all project can be changed in Directory.Build.props for 'Win32' and 'x64' platforms also;

If the solution consists of a mix of C++ native and .NET projects:

Critical Pitfall: Target C++ Specifically!
Global properties (like <LangVersion> or <PackageReference>) will break C++ builds.
The example of Directory.Build.props:
<Project>
	<!-- settings that apply to C++ projects; -->
	<PropertyGroup Condition="'$(MSBuildProjectExtension)' == '.vcxproj'">
		<SolutionDir Condition="'$(SolutionDir)' == ''">$(MSBuildThisFileDirectory)</SolutionDir>
		<OutDir>$(SolutionDir)bin\$(Platform)\$(Configuration)\</OutDir>
		<IntDir>$(SolutionDir)obj\$(MSBuildProjectName)\$(Platform)\$(Configuration)\</IntDir>
	</PropertyGroup>

	<!-- settings that apply to C# projects; -->
	<PropertyGroup Condition="'$(MSBuildProjectExtension)' == '.csproj'">
		<TargetFramework>net9.0</TargetFramework>
	</PropertyGroup>
</Project>

Best Practices for C++ Solutions:
(1) Use C++ Property Names: For output paths, C++ relies heavily on <OutDir> and <IntDir>.
    Do not use .NET-specific properties like <OutputPath> or <BaseOutputPath>.
(2) Avoid $(SolutionDir) at Root: When building individual projects via the command line, $(SolutionDir) evaluates to blank.
    Use $(MSBuildThisFileDirectory) as a fallback to ensure paths don't break.
(3) Inject Compiler and Linker Flags: You can easily inject global compiler options using <ItemDefinitionGroup> instead of a <PropertyGroup>:
    The example:
<ItemDefinitionGroup Condition="'$(MSBuildProjectExtension)' == '.vcxproj'">
	<ClCompile>
		<!-- sets C++ Language Standard across all projects; -->
		<LanguageStandard>stdcpp20</LanguageStandard>
		<WarningLevel>Level4</WarningLevel>
	</ClCompile>
</ItemDefinitionGroup>

The $([MSBuild]::GetPathOfFileAbove(string file, [string startingDirectory])) property function searches upward through parent directories for a specific file, returning its full path.
It starts in the specified or current directory, making it useful for importing shared root configurations like Directory.Build.props.
Common Uses
(1) Importing Parent Settings: Automatically locate and import custom props or target files from a parent folder or repository root.
(2) Chaining Configs: Combine with relative paths (like ../) to continue searching higher up when standard MSBuild traversal stops.

Code example:

<Import Condition="'$([MSBuild]::GetPathOfFileAbove('Common.props', '$(MSBuildThisFileDirectory)../'))' != ''"
	Project="$([MSBuild]::GetPathOfFileAbove('Common.props', '$(MSBuildThisFileDirectory)../'))" 
/>
