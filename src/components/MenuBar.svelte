<script lang="ts">
    import { invoke } from "@tauri-apps/api/core";
    let menuItems = [
        {
            label: "File",
            submenu: [
                { label: "New", action: () => handleNew() },
                { label: "Open", action: () => handleOpen() },
                { label: "Save", action: () => handleSave() },
                { label: "Exit", action: () => handleExit() },
            ],
        },
        {
            label: "Edit",
            submenu: [
                { label: "Undo", action: () => handleUndo() },
                { label: "Redo", action: () => handleRedo() },
                { label: "Cut", action: () => handleCut() },
                { label: "Copy", action: () => handleCopy() },
                { label: "Paste", action: () => handlePaste() },
            ],
        },
        {
            label: "Help",
            submenu: [{ label: "About", action: () => handleAbout() }],
        },
    ];
    // Functions for File menu
    async function handleNew() {
        await invoke("create_new_file");
    }

    function handleOpen() {
        console.log("Open clicked");
    }

    function handleSave() {
        console.log("Save clicked");
    }

    function handleExit() {
        console.log("Exit clicked");
    }

    // Functions for Edit menu
    function handleUndo() {
        console.log("Undo clicked");
    }

    function handleRedo() {
        console.log("Redo clicked");
    }

    function handleCut() {
        console.log("Cut clicked");
    }

    function handleCopy() {
        console.log("Copy clicked");
    }

    function handlePaste() {
        console.log("Paste clicked");
    }

    // Functions for Help menu
    function handleAbout() {
        console.log("About clicked");
    }

    let activeMenu: string | null = null;

    function toggleMenu(label: string) {
        activeMenu = activeMenu === label ? null : label;
    }

    function handleMouseOver(label: string) {
        if (activeMenu) {
            activeMenu = label;
        }
    }

    function handleFocus(label: string) {
        if (activeMenu) {
            activeMenu = label;
        }
    }
</script>

<div class="menubar">
    {#each menuItems as item}
        <button
            class="menu-item"
            on:click={() => toggleMenu(item.label)}
            on:mouseover={() => handleMouseOver(item.label)}
            on:focus={() => handleFocus(item.label)}
        >
            {item.label}
            {#if activeMenu === item.label}
                <div class="submenu">
                    {#each item.submenu as subItem}
                        <!-- svelte-ignore a11y_click_events_have_key_events -->
                        <!-- svelte-ignore a11y_no_static_element_interactions -->
                        <div class="submenu-item" on:click={subItem.action}>
                            {subItem.label}
                        </div>
                    {/each}
                </div>
            {/if}
        </button>
    {/each}
</div>

<style>
    .menubar {
        font-size: small;
        display: flex;
        padding-bottom: 5px;
        gap: 10px;
        background-color: transparent;
    }

    .menu-item {
        color: #cfcfcf;
        background-color: transparent;
        position: relative;
        cursor: pointer;
        border: none;
        border-radius: 4px;
        padding: 7px 15px 7px 15px;
        font-weight: inherit;
    }

    .menu-item:hover {
        background-color: #2a2a2a;
    }

    .submenu {
        position: absolute;
        top: 100%;
        left: 0;
        background-color: #2a2a2a;
        border: 1px solid #ccc;
        z-index: 1000;
    }

    .submenu-item {
        text-align: left;
        padding: 5px 8px;
        white-space: nowrap;
    }

    .submenu-item:hover {
        background-color: #f1f1f1;
    }
</style>
