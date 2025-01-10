<script lang="ts">
    import { onDestroy, onMount } from "svelte";
    import { editorViewStore } from "../../utils/fs";
    import { derived } from "svelte/store";
    import {
        activeTabId,
        editorTabs,
        type Tab,
    } from "../EditorPanel/editor_tabs-utils";
    import type { EditorView } from "codemirror";

    $: activeTab = $editorTabs.find((tab) => tab.id === $activeTabId);

    let editorContainer: HTMLElement;

    $: if (activeTab?.editorView && editorContainer) {
        editorContainer.innerHTML = "";
        editorContainer.appendChild(activeTab.editorView.dom);
        activeTab.editorView.focus();
    }

    $: console.log("activeTab:", activeTab);
</script>

<div bind:this={editorContainer} class="code-editor">
    {#if !activeTab?.editorView}
        Loading...
    {/if}
</div>

<style>
    @font-face {
        font-family: "Iosevka";
        src: url("/fonts/Iosevka-Regular.ttf") format("truetype");
        font-weight: normal;
        font-style: normal;
    }
    .code-editor {
        scroll-behavior: smooth;
        flex-grow: 1;
        overflow-y: auto;
    }
</style>
