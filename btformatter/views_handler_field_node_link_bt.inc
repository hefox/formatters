<?php
// $Id: views_handler_field_node_link_edit.inc,v 1.1 2008/09/03 19:21:29 merlinofchaos Exp $
/**
 * Field handler to present a link node edit.
 */
class views_handler_field_node_link_bt extends views_handler_field_node_link {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['title'] = 'title';
  }

  function render($values) {
    // ensure user has access to edit this node.
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->uid = $values->{$this->aliases['uid']};
    $node->title = $values->{$this->aliases['title']};
    $node->type = $values->{$this->aliases['type']};
    $node->status = 1; // unpublished nodes ignore access control
    if (!node_access('view', $node)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : $node->title;
    return btnodetitle($node, $text);
  }
}

