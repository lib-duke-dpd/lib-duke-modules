<?php

define('CALENDAR_ID_TAIL', '@group.calendar.google.com');

require_once "inc/gapi/apiClient.php";
require_once "inc/gapi/contrib/apiCalendarService.php";

function newApiCalendarService()
{
	date_default_timezone_set('America/New_York');
	$apiClient = new apiClient();
	$apiClient->setUseObjects(true);
	$service = new apiCalendarService($apiClient);

	return $service;
}

class CalendarManager
{
	protected $_calendarMap = array();
	protected $_availableCalendars = array();
	protected $_sourceFile = 'calendars.xml';
	protected $_defaultNumEvents = 7;
	protected $_calendarMode = 'week';
	protected $_lastStartTime = NULL;
	protected $_monthEvents = array();
	
	/**
	 * @Date array
	 * read-only
	 */
	private $_currentDate = NULL;
	
	/**
	 * Keep tabs of the previous start time
	 * when the "<< Prev" button is pressed
	 */
	private $_prevStartTime;
	
	/**
	 * same with the nextStartTime
	 */
	private $_nextStartTime;
	
	private $_startTime;
	
	public function __construct($loadNow = FALSE)
	{
		if ($loadNow) {
			$this->readCalendarMap();
		}
		
		// initialize nextStartTime and prevStartTime
		$now = getDate();
		$now_timestamp = mktime(0, 0, 0, $now['mon'], $now['mday'], $now['year']);
		$this->_currentDate = $now;
		
		if ($this->_calendarMode == 'week') {
			// determine actual date of 'Sunday' from now
			$delta_day = (int) date('w', $now_timestamp);
			$startTime = $now_timestamp - (86400 * $delta_day);
			$endTime = $now_timestamp + ((86400 * ($this->_defaultNumEvents - $delta_day)) - 1);
		} else {
			$startTime = $now_timestamp;
			$endTime = $now_timestamp + ((86400 * $this->_defaultNumEvents) - 1);
		}
		$this->_startTime = $now_timestamp;
		//echo sprintf("determined start time to be '%d'\n", $this->_startTime);
		$this->_nextStartTime = $endTime + 1;
		$this->_prevStartTime = $startTime - (86400 * 7);
	}
	
	public static function newCalendarManager($sourceFile)
	{
		$obj = new CalendarManager(FALSE);
		$obj->sourceFile = $sourceFile;
		$obj->readCalendarMap();
		return $obj;
	}
	
	public function __set($key, $value)
	{
		$method = 'set' . ucfirst($key);
		if (array_key_exists($key, $this->_calendarMap)) {
			$this->_calendarMap[$key] = $value;
			return $this;
		} else {
			if (!method_exists($this, $method)) {
				throw new Exception('Invalid property for "CalendarManager".');
			}
			return $this->$method($value);
		}
	}
	
	public function setCalendarMode($mode)
	{
		$this->_calendarMode = (string) $mode;
		return $this;
	}
	
	public function setDefaultNumEvents($n)
	{
		$this->_defaultNumEvents = $n;
		return $this;
	}
		
	public function setNextStartTime($time)
	{
		$this->_nextStartTime = $time;
		return $this;
	}
	
	public function setPrevStartTime($time)
	{
		$this->_prevStartTime = $time;
		return $this;
	}
	
	public function setSourceFile($file)
	{
		$this->_sourceFile = $file;
		return $this;
	}
	
	public function __get($key)
	{
		$method = 'get' . ucfirst($key);	
		if ('hours' == $key) {
			return $this->getHours();
		}
		if (array_key_exists($key, $this->_calendarMap)) {
			return $this->_calendarMap[$key];
		}
		if (!method_exists($this, $method)) {
			throw new Exception('Invalid property (' . $key . ') for "CalendarManager".');
		}
		return $this->$method();
	}

	public function getAvailableCalendars()
	{
		return $this->_availableCalendars;
	}
	
	public function getCalendarMode()
	{
		return $this->_calendarMode;
	}
	
	public function getCurrentDate()
	{
		return $this->_currentDate;
	}
	
	public function getDefaultNumEvents()
	{
		#throw new Exception($this->_defaultNumEvents);
		return $this->_defaultNumEvents;
	}
	
	public function getHours()
	{
		$return = array(
			'nextStartTime' => $this->_nextStartTime,
			'prevStartTime' => $this->_prevStartTime,
			'table' => array(),
			'assocTable' => array(),
		);
		foreach ($this->_calendarMap as $calId => $c) {
            if (!isset($c['hoursData'])) {
                continue;
            }
			$return['table'][] = array(
				'calendarId' => $calId,
				'libraryName' => $c['title'],
				'hoursData' => $c['hoursData'],
			);
			$return['assocTable'][$c['id']] = array(
				'calendarId'	=> $calId,
				'libraryName'	=> $c['title'],
				'hoursData'		=> $c['hoursData'],
			);
		}
		return $return;
	}
	
	public function getMonthEvents()
	{
		return $this->_monthEvents;
	}
	
	public function getNextStartTime()
	{
		return $this->_nextStartTime;
	}
	
	public function getPageData()
	{
		$headers = array();
		$rows = array();
		foreach ($this->_calendarMap as $calId => $data) {
			$libRow = array();
			$hoursData = $data['hoursData'];
			foreach ($hoursData as $h) {
				if (sizeof($headers) < sizeof($hoursData)) {
					$headers[] = array(
						'theDate' => $h->libraryDate['longDay'] . '<br />' 
							. $h->libraryDate['dateStr'],
						'currentDay' => $h->isCurrentDay)
					;
				}
				$libRow[] = array(
					'hours'		=> $h->hours,
					'currentDay'=> $h->isCurrentDay,
				);
			}
			#$rows[] = $libRow;
			$rows[] = array(
				'calId' => $calId,
				'libraryId' => $data['id'],
				'rowData' => $libRow,
			);
		}
		$headerTitle = date('l, F j', $this->_startTime) . ' - ' . date('l, F j', $this->_endTime);
		$arr = array(
			'headers'	=> $headers,
			'rows'		=> $rows,
			'lastStartTime'	=> $this->_lastStartTime,
			'prevStartTime' => $this->_prevStartTime,
			'nextStartTime' => $this->_nextStartTime,
			'currentDate'	=> $this->_currentDate,
			'headerTitle'	=> $headerTitle,
		);
		return $arr;
	}
	
	public function getPrevStartTime()
	{
		return $this->_prevStartTime;
	}
	
	public function getStartTime()
	{
		return $this->_startTime;
	}
	
	public function fetchMonth($libId, $service, $startTime)
	{
		# what month are we in...?
		$dArr = explode('|', date('n|Y', $startTime));
		$month = $dArr[0];
		$year = $dArr[1];
		
		# how about the number of days?
		$numDaysInMonth = (int) date('t', $startTime);
		
		if ((int) date('j', $startTime) != 1) {
			$firstDayOfMonth = mktime(0, 0, 0, $month, 1, (int) date('Y', $startTime));
		} else {
			$arr = getDate($startTime);
			$firstDayOfMonth = mktime(0, 0, 0, $arr['mon'], $arr['mday'], $arr['year']);
		}
		$lastDayOfMonth = mktime(23, 59, 59, $month, $numDaysInMonth, $year);
		
		# when is the first Sunday
		$firstSunday = $firstDayOfMonth - (86400 * (int)date('w', $firstDayOfMonth));
		$lastSaturday = $lastDayOfMonth + ((6 - (int)date('w', $lastDayOfMonth)) * 86400);
		$numEvents = (int)date('z', $lastSaturday) - (int)date('z', $firstSunday) + 1;
		
		//echo sprintf("First Sunday = [%s]; Last Saturday is [%s]<br />\n", 
		//	date('M j, Y', $firstSunday), date('M j, Y', $lastSaturday));
		
		$params = array(
			'timeMin' => date('Y-m-d', $firstSunday) . 'T00:00:00-05:00',
			'singleEvents' => true,
			'orderBy' => 'startTime',
			'maxResults' => $numEvents,
		);
		// find the calendarID for libId
		$fn = function($var)
		{
			global $libId;
			return $var['libraryId'] == $libId;
		};
		$z = array_filter($this->availableCalendars, $fn);
		$entry = array_pop($z);
		$calId = $entry['calId'];
		
		$events = $service->events->listEvents($calId . CALENDAR_ID_TAIL, $params);

		$monthEvents = array();
		#$thisWeek = array();
		foreach ($events->items as $eventItem) {
			$this->_monthEvents[] = $this->_event_fc_object($eventItem);
		}
	}
	
	/**
	 * Alias to new 'fetchWeek'
	 */
	public function fetchHours($options, $service, $now = NULL)
	{
		$this->fetchWeek($options, $service, $now);
	}

    /**
     * Fetchs Google calendar data for all applicable
     * Duke library calendar feeds.
     *
     * @param $variables
     *   An associative array containing (but not limited to):
     *   - firstDay
     *   - numEvents
     *   - limitLibraries => array of libraries to query
     */
	public function fetchWeek($options, $service, $now = NULL)
	{
		if ($now == NULL) {
			$now = getDate();
		} else {
			# accept whatever date is supplied by the front end
			$now = getDate($now);
		}
		$now_timestamp = mktime(0, 0, 0, $now['mon'], $now['mday'], $now['year']);
		$this->_currentDate = getDate();
		
		$this->_lastStartTime = array(
			'timestamp'		=> $now,
			'dateStr'		=> date('D n/j', $now_timestamp),
		);
		
		$startTime = '';	// TBD.
		$endTime = '';		// TBD
		
		$firstDay = array_key_exists('firstDay', $options) 
			? $options['firstDay'] 
			: 'Sunday';
		
		$numEvents = array_key_exists('numEvents', $options)
			? (int) $options['numEvents']
			: (($firstDay == 'Sunday') ? 7 : $this->_defaultNumEvents);
			
		if ('Sunday' == $firstDay) {
			// determine actual date of 'Sunday' from now
			$delta_day = (int) date('w', $now_timestamp);
			$startTime = $now_timestamp - (86400 * $delta_day);
			$endTime = $now_timestamp + ((86400 * ($numEvents - $delta_day)) - 1);
		} else {
			$startTime = $now_timestamp;
			$endTime = $now_timestamp + ((86400 * $numEvents) - 1);
		}
		$this->_nextStartTime = $endTime + 1;
		$this->_prevStartTime = $startTime - (86400 * 7);
		
		$params = array(
			'timeMin' => date('Y-m-d', $startTime) . 'T00:00:00-05:00',
			'singleEvents' => true,
			'orderBy' => 'startTime',
			'maxResults' => $numEvents,
		);
			
		$hasSelection = (array_key_exists('libraries', $options) && count($options['libraries']));
		foreach ($this->_calendarMap as $calId => $calMapData) {
			$bool = true;
			if ($hasSelection) {
				if (!in_array($calMapData['id'], $options['libraries'])) {
					$bool = false;
				}
			}
			if ($bool) {
				$events = $service->events->listEvents($calId . CALENDAR_ID_TAIL, $params);
				foreach ($events->items as $eventItem) {
					if (!array_key_exists('hoursData', $this->_calendarMap[$calId])) {
						$this->_calendarMap[$calId]['hoursData'] = array();
					}
					$this->_calendarMap[$calId]['hoursData'][] = 
                        $this->_event_date_object($eventItem, $calMapData['title']);
				}
			}
		}
	}
	
	protected function _event_fc_object($eventItem)
	{
		$o = new StdClass();
		$tmp = $this->_event_date_object($eventItem, NULL);
		
		$o->title = $tmp->hours;
		$o->allDay = TRUE;
		$o->start = $tmp->timestamp;
		
		return $o;
	}
	
	protected function _event_date_object($eventItem, $libraryName)
	{		
		$object = new StdClass();
		
		if (isset($eventItem->start->dateTime)) {
			$convertedTime = strtotime($eventItem->start->dateTime);
		} else {
			$convertedTime = strtotime($eventItem->start->date);
		}
		
		$object->isCurrentDay = ((int) date('z', $convertedTime) == (int) $this->_currentDate['yday']);
		$object->libraryDate = array(
			'dayAndDate' => date('D n/j', $convertedTime),
			'shortDay' => date('D', $convertedTime),
			'longDay' => date('l', $convertedTime),
			'dateStr' => date('n/j', $convertedTime),
			'wday' => (int)date('w', $convertedTime),
			'yday' => (int)date('z', $convertedTime),
		);
		$object->timestamp = $convertedTime;
			
		if ($eventItem->summary == 'Perkins Hours: Close at Midnight') {
			$object->hours = 'Close at Midnight';
		} else if ($eventItem->summary == 'CLOSED') {
			$object->hours = 'Closed';
		} else if (isset($eventItem->start->dateTime)) {
			$startDateTime = strtotime($eventItem->start->dateTime);
			$endDateTime = strtotime($eventItem->end->dateTime);
	
			// we need to account for the special case when the 
			// end date is actually 23:59
			if (date('i', $endDateTime) == '59' && date('D', $endDateTime) == 'Sun') {
				// set the 'Hours' attribute to 'Open at <startTime>'
				$object->hours = 'Open at ' . date('ga', $startDateTime);
			} else {        
				$_start = date('i', $startDateTime) == '00'
					? date('ga', $startDateTime)
					: date('g:ia', $startDateTime);
				$_end = date('i', $endDateTime) == '00'
					? date('ga', $endDateTime)
					: date('g:ia', $endDateTime);
				$object->hours = $_start . ' &ndash; ' . $_end;   
			}
		} else {
			// we have a date
			$startDate = strtotime($eventItem->start->date);
			
			if (date('D', $startDate) == 'Fri') {
				$object->hours = 'Closes at Midnight';
			} else {
				$object->hours = 'Open 24 Hours';
			}
		}
		return $object;
	}
	
	public function readCalendarMap()
	{
		try {
			$file_contents = file_get_contents($this->_sourceFile);
			$xml = new SimpleXMLElement($file_contents);
			foreach ($xml->children() as $calendar) {
				$newKey = (string) $calendar['id'];
				$this->_availableCalendars[] = array(
					'libraryName'	=> (string) $calendar->libraryName,
					'libraryId'		=> (string) $calendar->libraryId,
					'calId'			=> $newKey
				);
				$this->_calendarMap[$newKey] = array(
					'title' => (string) $calendar->libraryName,
					'id'	=> (string) $calendar->libraryId,
				);
				#$this->_calendarMap[$newKey] = (string) $calendar->libraryName;
			}
		} catch (Exception $e) {
			echo $e->getMessage();
		}
	}
}

?>
