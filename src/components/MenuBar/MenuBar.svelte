<script lang="ts">
  import { menuItems } from "./menu-data";
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
