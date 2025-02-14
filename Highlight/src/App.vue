<script setup>
import { onMounted } from 'vue'
import {editor} from 'monaco-editor'
import EditorWorker from 'monaco-editor/esm/vs/editor/editor.worker?worker'

onMounted(() => {
    const div = document.getElementById('container');
    self.MonacoEnvironment = 
    {
        getWorker(workerId, label)
        {
            return new EditorWorker();
        }
    }
    self.Print = () => 
    {
        console.log('Print called');
    };
//     window.editor = editor.create(div, 
//     {
//         value: `#include <iostream>
// int main()
// {
//     std::cout << "Hello World!";
//     return 0;
// }
//     `,
//         automaticLayout: true,
//         readOnly: true,
//         "semanticHighlighting.enabled": true,
//         language: 'cpp',
//         theme: 'vs-dark'
//     });
    window.create = editor.create;
});

</script>

<template>
    <div id="container" style="height: 100vh;width: 100%;overflow: auto;background-color: red;"></div>
</template>