<script lang="ts">
    import { onMount } from "svelte";
    import { EditorView, basicSetup } from "codemirror";
    import { EditorState } from "@codemirror/state";
    import { cpp } from "@codemirror/lang-cpp";
    import {
        createVitesseDarkTheme,
        vitesseDark,
    } from "codemirror-theme-vitesse";
    import { editorViewStore } from "../utils/fs";

    const vitesseDarkCustom = createVitesseDarkTheme({
        settings: {
            background: "transparent",
            gutterBackground: "transparent",
            lineHighlight: "transparent",
            gutterActiveForeground: "#bfbaaa",
        },
    });

    export let editorView: EditorView;
    export let editorElement: Element | DocumentFragment;

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
                    basicSetup,
                    cpp(),
                    vitesseDarkCustom,
                    customTheme,
                    EditorView.lineWrapping,
                ],
                doc: "",
            }),

            parent: editorElement,
        });

        editorViewStore.set(editorView);

        return () => {
            editorView.destroy();
        };
    });
</script>

<div bind:this={editorElement} class="code-editor"></div>

<style>
    @font-face {
        font-family: "Iosevka";
        src: url("/fonts/Iosevka-Regular.ttf") format("truetype");
        font-weight: normal;
        font-style: normal;
    }
    .code-editor {
        scroll-behavior: smooth;
        height: 100%;
        flex-grow: 1;
    }
</style>
