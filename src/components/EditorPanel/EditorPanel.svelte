<script>
    import CodeEditor from "./CodeEditor.svelte";
    import { editorTabs } from "./editor_tabs-utils";
    import EditorTabs from "./EditorTabs.svelte";
    import RunIcon from "../../assets/run.svg";
</script>

<div class="container">
    <div class="tab-gutter">
        <EditorTabs />
        <button class="run-button">
            <img src={RunIcon} alt="Run Source File Button" width="19px" />
            Run Code
        </button>
    </div>
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
        justify-content: center;
        background-color: #202020;
        border-radius: 8px;
        height: 100%;
        overflow-y: auto;
    }
    .empty {
        margin: auto;
    }
    .tab-gutter {
        display: flex;
        justify-content: space-between;
        background-color: #181818;
        gap: 5px;
    }
    .run-button {
        display: flex;
        flex-shrink: 0;
        align-items: center;
        background-color: #5da977;
        border-radius: 3px;
        margin-right: 10px;
        height: 30px;
        border: none;
        padding-left: 8px;
        padding-right: 8px;
        cursor: pointer;
    }
</style>
