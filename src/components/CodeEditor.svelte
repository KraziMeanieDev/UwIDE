<script>
    import { onMount } from "svelte";
    import { EditorView, basicSetup } from "codemirror";
    import { EditorState } from "@codemirror/state";
    import { cpp } from "@codemirror/lang-cpp";
    import {
        createVitesseDarkTheme,
        vitesseDark,
    } from "codemirror-theme-vitesse";

    const vitesseDarkCustom = createVitesseDarkTheme({
        settings: {
            background: "transparent",
            gutterBackground: "transparent",
            lineHighlight: "transparent",
            gutterActiveForeground: "#bfbaaa",
        },
    });

    // @ts-ignore
    let editorView;
    // @ts-ignore
    let editorElement;

    onMount(() => {
        const customTheme = EditorView.theme({
            "&": {
                fontSize: "16px",
            },
            ".cm-content": {
                fontFamily: '"Iosevka", monospace',
            },
            ".cm-lineNumbers .cm-gutterElement": {
                fontFamily: '"Iosevka", monospace',
            },
        });
        // Initialize the editor
        editorView = new EditorView({
            state: EditorState.create({
                extensions: [
                    basicSetup, // Basic editor setup (line numbers, etc.)
                    cpp(), // C++ syntax highlighting
                    vitesseDarkCustom,
                    customTheme,
                    EditorView.lineWrapping,
                ],
                doc: `#include <iostream>\n\nint main() {\n    std::cout << "Hello, World!" << std::endl;\n    return 0;\n}`,
            }),
            // @ts-ignore
            parent: editorElement,
        });

        // Cleanup on component destruction
        return () => {
            // @ts-ignore
            editorView.destroy();
        };
    });
</script>

<div bind:this={editorElement} class="code-editor"></div>

<style>
    @font-face {
        font-family: "Iosevka";
        src: url("/fonts/Iosevka-Regular.ttf") format("truetype");
        /* Add other formats if needed, e.g., woff2 */
        font-weight: normal;
        font-style: normal;
    }
    .code-editor {
        scroll-behavior: smooth;
        height: 100%;
        flex-grow: 1;
    }
</style>
