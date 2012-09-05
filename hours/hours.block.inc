<?php

/**
 * @file 
 * User block views for Hours module
 */
 
/**
 * Block display for 'Frontpage' hours table
 */
function hours_block_view_frontpage() {
	try {
		$calendarManager = CalendarManager::getInstance(
			drupal_get_path('module', 'hours') . '/calendars.xml');
			
		$options = array(
			'firstDay' => date('l'),
			'numEvents' => 4,
			'libraries' => array('perkins','public'),
		);
		$calendarManager->fetchHours($options, newApiCalendarService(), time());
		$hours = $calendarManager->hours;
		$items = array();
	
		$perkins = $hours['assocTable']['perkins']['hoursData'];
		$public = $hours['assocTable']['public']['hoursData'];
		for ($i = 0; $i < count($perkins); $i++) {
			$items[] = theme('hours_block_item', array('duke' => $perkins[$i], 'public' => $public[$i]));
		}
		#watchdog('hours_block_view', print_r($items, TRUE));

		$block['content'] = theme('hours_block_items', array('items' => $items));
		$block['subject'] = 'Perkins/Bostock Hours';
		return $block;

	} catch(Exception $e) {
		return t('Hours block currently unavailable');
	}
}
