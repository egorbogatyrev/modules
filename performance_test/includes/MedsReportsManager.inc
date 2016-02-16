<?php

/**
 * @file
 * Contains MedsReportsReportManager class.
 */

/**
 * The class for managing reports.
 */
class PerformanceTestManager {

  /**
   * Basic factory function for report plugins.
   */
  public static function factory($plugin) {

    // Make sure that the handler class exists and that it has this class
    // as one of its parents.
    if (class_exists($plugin['handler']['class'])) {
      return new $plugin['handler']['class']($plugin);
    }
    else {
      // The plugin handler class is defined but it can't be found.
      watchdog('meds_reports', 'Class <em>!name</em> is not exists!', array('!name' => $plugin['handler']['class']), WATCHDOG_ERROR);
    }
  }
}
