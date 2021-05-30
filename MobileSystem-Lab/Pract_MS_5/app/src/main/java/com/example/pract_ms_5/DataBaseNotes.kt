package com.example.pract_ms_5

import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.DatabaseUtils
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

class DataBaseNotes(context: Context?) : SQLiteOpenHelper(context, DATABASE_NAME, null, 1) {

    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL("CREATE TABLE $NOTE_TABLE_NAME (" +
                "$NOTE_COLUMN_NOTE VARCHAR(255) PRIMARY KEY)" );
    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        db.execSQL("DROP TABLE IF EXISTS $NOTE_TABLE_NAME");
        onCreate(db);
    }

    fun InsertNote(note: String): Boolean {
        val db = this.writableDatabase;
        val contentValues = ContentValues();
        contentValues.put(NOTE_COLUMN_NOTE, note);

        return db.insert(NOTE_TABLE_NAME, null, contentValues) != (0).toLong();
    }

    fun NumberOfRows(): Int {
        val db = this.readableDatabase;
        return DatabaseUtils.queryNumEntries(db, NOTE_TABLE_NAME).toInt();
    }

    fun UpdateNote(note: String): Boolean {
        val db = this.writableDatabase;
        val contentValues = ContentValues();
        contentValues.put(NOTE_COLUMN_NOTE, note);

        return db.update(NOTE_TABLE_NAME, contentValues, "$NOTE_COLUMN_NOTE = ? ", arrayOf(note)) != 0;
    }

    fun DeleteNote(note: String): Int {
        val db = this.writableDatabase
        return db.delete(NOTE_TABLE_NAME,
            "$NOTE_COLUMN_NOTE = ? ", arrayOf(note))
    }

    fun Notes(): ArrayList<String> {
        val listSaves = ArrayList<String>()

        val db = this.readableDatabase
        val res: Cursor = db.rawQuery("select * from $NOTE_TABLE_NAME", null)
        res.moveToFirst()
        while (!res.isAfterLast) {
            listSaves.add(res.getString(res.getColumnIndex(NOTE_COLUMN_NOTE)));
            res.moveToNext()
        }
        res.close();
        return listSaves
    }

    companion object {
        const val DATABASE_NAME = "NoteDB.db";
        const val NOTE_TABLE_NAME = "notes";
        const val NOTE_COLUMN_NOTE = "note";
    }
}