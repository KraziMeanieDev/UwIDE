<script lang="ts">
    import { editorTabs, activeTabId, removeTab } from "./editor_tabs-utils";
    import { slide } from "svelte/transition";
    import XMarkIcon from "../../assets/xmark.svg";

    async function handleCloseTab(tabId: string, activeTabId: string) {
        await removeTab(tabId, activeTabId);
    }

    async function handleSetActiveTabOnClick(tabId: string) {
        await activeTabId.set(tabId);
    }
</script>

<div class="editor-tab-list">
    {#each $editorTabs as tab (tab.id)}
        <!-- svelte-ignore a11y_click_events_have_key_events -->
        <!-- svelte-ignore a11y_no_static_element_interactions -->
        <div
            class="editor-tab"
            class:active={$activeTabId === tab.id}
            transition:slide={{ duration: 200 }}
            on:click={() => handleSetActiveTabOnClick(tab.id)}
        >
            <span class="tab-title">{tab.title}</span>
            <button
                class="tab-close-button"
                on:click={() => handleCloseTab(tab.id, $activeTabId)}
            >
                <img src={XMarkIcon} alt="Tab Close Button" width="16px" />
            </button>
        </div>
    {/each}
</div>

<style>
    .editor-tab-list {
        background-color: #181818;
        display: flex;
        position: sticky;
        font-size: 0.9rem;
    }
    .editor-tab {
        display: flex;
        height: 35px;
        width: 150px;
        justify-content: space-between;
        align-items: center;
        padding-left: 10px;
        padding-right: 10px;
        border-top-left-radius: 8px;
        border-top-right-radius: 8px;
        cursor: pointer;
    }
    .editor-tab:not(.active):hover {
        background: #2b2b2b; /* Example hover background color for inactive tabs */
    }
    .editor-tab.active {
        /* Style for the active tab */
        background-color: #202020; /* Example active background color */
        /* You can add other styles here to visually distinguish the active tab */
        font-weight: bold; /* Example: make the title bold */
    }
    .tab-title {
        justify-content: space-between;
        white-space: nowrap;
        overflow: hidden;
        text-overflow: ellipsis;
        display: inline-block;
    }
    .tab-close-button {
        background: transparent;
        border: none;
        padding: 0.3rem;
        cursor: pointer;
        display: flex;
        align-items: center;
        justify-content: center;
        border-radius: 4px;
    }

    .tab-close-button:hover {
        background-color: #404040;
    }
</style>
