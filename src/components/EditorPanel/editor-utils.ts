import { EditorView, basicSetup } from "codemirror";
import { EditorState } from "@codemirror/state";
import { cpp } from "@codemirror/lang-cpp";
import {
    createVitesseDarkTheme,
    vitesseDark,
} from "codemirror-theme-vitesse";
import { readTextFile } from "@tauri-apps/plugin-fs";

const vitesseDarkCustom = createVitesseDarkTheme({
    settings: {
        background: "transparent",
        gutterBackground: "transparent",
        lineHighlight: "transparent",
        gutterActiveForeground: "#bfbaaa",
    },
});

const customEditorTheme = EditorView.theme({
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

const createBaseEditorState = (doc = "") => EditorState.create({
    extensions: [
        basicSetup,
        cpp(),
        vitesseDarkCustom,
        customEditorTheme,
        EditorView.lineWrapping,
    ],
    doc: doc,
});

export function createInitialEditorView(): EditorView {
    return new EditorView({ state: createBaseEditorState() });
}

export async function createNewEditorView(filePath: string): Promise<EditorView | null> {
    try {
        const result = await readTextFile(filePath);
        return new EditorView({
            state: createBaseEditorState(result),
        });
    } catch (error) {
        console.error("Error reading file:", error);
        return null;
    }
}