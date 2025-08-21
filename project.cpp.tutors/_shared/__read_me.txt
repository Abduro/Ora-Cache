:: the files in this folder are most likely copied from the Ebo Pack solution and perhaps a little bit modified,
:: but it is acceptable for supporting high isolation level between the solutions;

::*important*:
:: in the project file each node <ItemDefinitionGroup>/<ClCompile> must contain <PreprocessorDefinitions> sub-node for working prerocessor defs properly:
:: for example:
:: <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
::    <ClCompile>
::       <PreprocessorDefinitions>_DEBUG;WIN64;%(PreprocessorDefinitions)</PreprocessorDefinitions>
::    </ClCompile>
:: </ItemDefinitionGroup>
::
:: The preprocessor definition must contain 'WIN64' or 'WIN32' either in accordance with project's platform (x64/Win32);