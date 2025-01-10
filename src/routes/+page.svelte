<script lang="ts">
  import ConsolePanel from "../components/ConsolePanel.svelte";
  import EditorPanel from "../components/EditorPanel/EditorPanel.svelte";
  import ExplorerPanel from "../components/ExplorerPanel.svelte";
  import MenuBar from "../components/MenuBar/MenuBar.svelte";
</script>

<main class="container">
  <MenuBar />
  <div class="parent-layout">
    <ExplorerPanel />
    <div class="nested-layout">
      <EditorPanel />
      <!-- <ConsolePanel /> -->
    </div>
  </div>
</main>

<style>
  :root {
    line-height: 24px;
    margin: 0;
    /*    font-weight: normal;*/

    color: #0f0f0f;
    background-color: #f6f6f6;

    font-synthesis: none;
    text-rendering: optimizeLegibility;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    -webkit-text-size-adjust: 100%;
    user-select: none;
  }

  .container {
    padding: 5px;
    display: flex;
    flex-direction: column;
    height: 100vh;
    box-sizing: border-box;
  }

  .parent-layout {
    display: flex;
    flex-grow: 1;
    gap: 5px;
    overflow: hidden;
  }

  .nested-layout {
    display: flex;
    flex-direction: column;
    flex-grow: 1;
    width: 100%;
    gap: 5px;
    overflow: hidden;
  }

  @media (prefers-color-scheme: dark) {
    :root {
      color: #cfcfcf;
      background-color: #181818;
    }
  }
</style>
