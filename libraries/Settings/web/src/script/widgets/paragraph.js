import { Component } from "@alexgyver/component";
import WidgetBase from "./widget";
import './paragraph.css';

export default class ParagraphWidget extends WidgetBase {
    constructor(data) {
        super(data, !!data.label);

        super.addChild(Component.make('p', {
            context: this,
            var: 'out',
            class: 'paragraph',
        }));

        this.update(data.value);
    }

    update(value) {
        this.$out.innerText = value ?? '';
    }
}