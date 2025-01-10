<script>
    import { editorViewStore } from "../../utils/fs";
    import CodeEditor from "./CodeEditor.svelte";
    import { activeTabId, editorTabs } from "./editor_tabs-utils";
    import XMarkIcon from "../../assets/xmark.svg";
    import EditorTabs from "./EditorTabs.svelte";

    // console.log($editorTabs, $activeTabId);
</script>

<div class="container">
    <EditorTabs />
    {#if $editorTabs.length === 0}
        <div class="empty">Hello World</div>
    {:else}
        <CodeEditor />
    {/if}
</div>

<style>
    .container {
        display: flex;
        flex-direction: column;
        background-color: #202020;
        border-radius: 8px;
        height: 100%;
        overflow-y: auto;
    }
    .empty {
        margin: auto;
    }
</style>
