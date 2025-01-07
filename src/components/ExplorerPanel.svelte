<script lang="ts">
    import { onMount } from "svelte";
    import { currentFolderItems, loadFile } from "../utils/fs";

    onMount(() => {
        console.log($currentFolderItems);
    });

    function handleFolderSelect(path: String) {}

    async function handleFileSelect(path: string) {
        await loadFile(path);
    }
</script>

<div class="container">
    <div class="header">Explorer</div>
    <div class="entry-list">
        {#each $currentFolderItems as entry}
            <!-- svelte-ignore a11y_click_events_have_key_events -->
            <!-- svelte-ignore a11y_no_static_element_interactions -->
            <span
                class="entry-name"
                on:click={entry.isDirectory
                    ? () => handleFolderSelect(entry.path)
                    : () => handleFileSelect(entry.path)}>{entry.name}</span
            >
        {/each}
    </div>
</div>

<style>
    .container {
        display: flex;
        flex-direction: column;
        background-color: #202020;
        width: 225px;
        min-width: 200px;
        border-radius: 8px;
    }

    .header {
        display: flex;
        height: 35px;
        width: 100%;
        border-bottom: 2px solid #323232;
        align-items: center;
        padding-left: 15px;
        position: sticky;
    }
    .entry-list {
        display: flex;
        flex-direction: column;
        height: 100%;
        overflow-y: auto;
    }
    .entry-list > span {
        display: flex;
        align-items: center;
        min-height: 35px;
        padding-left: 15px;
    }
    .entry-list > span:hover {
        background-color: #2a2a2a;
    }
    .entry-name {
        white-space: nowrap; /* Prevent text from wrapping */
        overflow: hidden; /* Hide overflow content */
        text-overflow: ellipsis; /* Add ... at the end */
        display: inline-block;
    }
</style>
