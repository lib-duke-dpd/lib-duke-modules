<?php
$page = new stdClass();
$page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
$page->api_version = 1;
$page->name = 'collections_page_template';
$page->task = 'page';
$page->admin_title = 'Collections Page Template';
$page->admin_description = 'This page should not be used -- it is simply a placeholder page from which code can be exported from.';
$page->path = 'collections/main';
$page->access = array();
$page->menu = array();
$page->arguments = array();
$page->conf = array(
  'admin_paths' => FALSE,
);
$page->default_handlers = array();
$handler = new stdClass();
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'page_collections_page_template_panel_context';
$handler->task = 'page';
$handler->subtask = 'collections_page_template';
$handler->handler = 'panel_context';
$handler->weight = 0;
$handler->conf = array(
  'title' => 'Collections Page - Master',
  'no_blocks' => 0,
  'pipeline' => 'standard',
  'body_classes_to_remove' => '',
  'body_classes_to_add' => '',
  'css_id' => '',
  'css' => '',
  'contexts' => array(),
  'relationships' => array(),
);
$display = new panels_display();
$display->layout = 'flexible';
$display->layout_settings = array(
  'items' => array(
    'canvas' => array(
      'type' => 'row',
      'contains' => 'column',
      'children' => array(
        0 => 1,
        1 => 'main',
        2 => 2,
      ),
      'parent' => NULL,
    ),
    'main' => array(
      'type' => 'column',
      'width' => '50',
      'width_type' => '%',
      'children' => array(
        0 => 'main-row',
      ),
      'parent' => 'canvas',
    ),
    'main-row' => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'center',
      ),
      'parent' => 'main',
    ),
    'center' => array(
      'type' => 'region',
      'title' => 'Center',
      'width' => 100,
      'width_type' => '%',
      'parent' => 'main-row',
    ),
    1 => array(
      'type' => 'column',
      'width' => '25',
      'width_type' => '%',
      'parent' => 'canvas',
      'children' => array(
        0 => 3,
      ),
      'class' => '',
    ),
    2 => array(
      'type' => 'column',
      'width' => '25',
      'width_type' => '%',
      'parent' => 'canvas',
      'children' => array(
        0 => 4,
      ),
      'class' => '',
    ),
    3 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'facet_region',
      ),
      'parent' => '1',
      'class' => '',
    ),
    'facet_region' => array(
      'type' => 'region',
      'title' => 'Facet Region',
      'width' => 100,
      'width_type' => '%',
      'parent' => '3',
      'class' => 'facet-region',
    ),
    4 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'right_sidebar',
      ),
      'parent' => '2',
      'class' => '',
    ),
    'right_sidebar' => array(
      'type' => 'region',
      'title' => 'Right Sidebar',
      'width' => 100,
      'width_type' => '%',
      'parent' => '4',
      'class' => 'right-sidebar',
    ),
  ),
);
$display->panel_settings = array(
  'style_settings' => array(
    'default' => NULL,
    'center' => NULL,
    'facet_region' => NULL,
    'right_sidebar' => NULL,
  ),
);
$display->cache = array();
$display->title = 'No Title';
$display->content = array();
$display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-1';
  $pane->panel = 'center';
  $pane->type = 'block';
  $pane->subtype = 'block-28';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-1'] = $pane;
  $display->panels['center'][0] = 'new-1';
  $pane = new stdClass();
  $pane->pid = 'new-2';
  $pane->panel = 'facet_region';
  $pane->type = 'block';
  $pane->subtype = 'block-27';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-2'] = $pane;
  $display->panels['facet_region'][0] = 'new-2';
$display->hide_title = PANELS_TITLE_FIXED;
$display->title_pane = '0';
$handler->conf['display'] = $display;
$page->default_handlers[$handler->name] = $handler;
?>